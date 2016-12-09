/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "cpptoolsplugin.h"
#include "cppcompletionassist.h"
#include "cppmodelmanager.h"

#include <texteditor/plaintexteditor.h>
#include <texteditor/codeassist/iassistproposal.h>

#include <utils/changeset.h>
#include <utils/fileutils.h>

#include <QtTest>
#include <QDebug>
#include <QTextDocument>
#include <QDir>

/*!
    Tests for code completion.
 */
using namespace CPlusPlus;
using namespace CppTools;
using namespace CppTools::Internal;
using namespace TextEditor;
using namespace Core;

class CompletionTestCase
{
public:
    CompletionTestCase(const QByteArray &sourceText, const QByteArray &textToInsert = QByteArray())
        : position(-1), editorWidget(0), textDocument(0), editor(0),
          cmm(CppModelManager::instance())
    {
        source = sourceText;
        position = source.indexOf('@');
        QVERIFY(position != -1);
        source[position] = ' ';

        // Write source to file
        const QString fileName = QDir::tempPath() + QLatin1String("/file.h");
        Utils::FileSaver srcSaver(fileName);
        srcSaver.write(source);
        srcSaver.finalize();

        // Open in editor
        editor = EditorManager::openEditor(fileName);
        QVERIFY(editor);
        editorWidget = qobject_cast<TextEditor::BaseTextEditorWidget *>(editor->widget());
        QVERIFY(editorWidget);

        textDocument = editorWidget->document();

        // Get Document
        while (!cmm->snapshot().contains(fileName))
            QCoreApplication::processEvents();
        Document::Ptr document = cmm->snapshot().document(fileName);

        snapshot.insert(document);

        if (!textToInsert.isEmpty())
            insertText(textToInsert);
    }

    ~CompletionTestCase()
    {
        EditorManager::instance()->closeEditors(QList<IEditor*>() << editor,
                                                /*askAboutModifiedEditors=*/ false);
        cmm->GC();
        QVERIFY(cmm->snapshot().isEmpty());
    }

    QStringList getCompletions(bool *replaceAccessOperator = 0) const
    {
        QStringList completions;
        CppCompletionAssistInterface *ai
            = new CppCompletionAssistInterface(editorWidget->document(), position,
                                               editorWidget->editorDocument()->fileName(),
                                               ExplicitlyInvoked, snapshot,
                                               QStringList(), QStringList());
        CppCompletionAssistProcessor processor;
        IAssistProposal *proposal = processor.perform(ai);
        if (!proposal)
            return completions;
        IAssistProposalModel *model = proposal->model();
        if (!model)
            return completions;
        CppAssistProposalModel *listmodel = dynamic_cast<CppAssistProposalModel *>(model);
        if (!listmodel)
            return completions;

        for (int i = 0; i < listmodel->size(); ++i)
            completions << listmodel->text(i);

        if (replaceAccessOperator)
            *replaceAccessOperator = listmodel->m_replaceDotForArrow;

        return completions;
    }

    void insertText(const QByteArray &text)
    {
        Utils::ChangeSet change;
        change.insert(position, QLatin1String(text));
        QTextCursor cursor(textDocument);
        change.apply(&cursor);
        position += text.length();
    }

private:
    QByteArray source;
    int position;
    Snapshot snapshot;
    BaseTextEditorWidget *editorWidget;
    QTextDocument *textDocument;
    IEditor *editor;

    CppModelManager *cmm;
};

void CppToolsPlugin::test_completion_forward_declarations_present()
{
    const QByteArray source =
        "\n"
        "class Foo\n"
        "{\n"
        "    struct Bar;\n"
        "    int i;\n"
        "};\n"
        "\n"
        "struct Foo::Bar \n"
        "{\n"
        "    Bar() {}\n"
        "};\n"
        "\n"
        "@\n"
        "// padding so we get the scope right\n";
    CompletionTestCase test(source, "Foo::Bar::");

    QStringList expected;
    expected.append(QLatin1String("Bar"));

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions, expected);
}

void CppToolsPlugin::test_completion_inside_parentheses_c_style_conversion()
{
    const QByteArray source = "\n"
            "class Base\n"
            "{\n"
            "    int i_base;\n"
            "};\n"
            "\n"
            "class Derived : public Base\n"
            "{\n"
            "    int i_derived;\n"
            "};\n"
            "\n"
            "void fun()\n"
            "{\n"
            "    Base *b = new Derived;\n"
            "    if (1)\n"
            "        @\n"
            "}\n"
            ;
    CompletionTestCase test(source, "((Derived *)b)->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 4);
    QVERIFY(completions.contains(QLatin1String("Derived")));
    QVERIFY(completions.contains(QLatin1String("Base")));
    QVERIFY(completions.contains(QLatin1String("i_derived")));
    QVERIFY(completions.contains(QLatin1String("i_base")));
}

void CppToolsPlugin::test_completion_inside_parentheses_cast_operator_conversion()
{
    const QByteArray source = "\n"
            "class Base\n"
            "{\n"
            "    int i_base;\n"
            "};\n"
            "\n"
            "class Derived : public Base\n"
            "{\n"
            "    int i_derived;\n"
            "};\n"
            "\n"
            "void fun()\n"
            "{\n"
            "    Base *b = new Derived;\n"
            "    if (1)\n"
            "        @\n"
            "}\n"
            ;
    CompletionTestCase test(source, "(static_cast<Derived *>(b))->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 4);
    QVERIFY(completions.contains(QLatin1String("Derived")));
    QVERIFY(completions.contains(QLatin1String("Base")));
    QVERIFY(completions.contains(QLatin1String("i_derived")));
    QVERIFY(completions.contains(QLatin1String("i_base")));
}

void CppToolsPlugin::test_completion_basic_1()
{
    const QByteArray source = "\n"
            "class Foo\n"
            "{\n"
            "    void foo();\n"
            "    int m;\n"
            "};\n"
            "\n"
            "void func() {\n"
            "    Foo f;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source);

    QStringList basicCompletions = test.getCompletions();
    QVERIFY(!basicCompletions.contains(QLatin1String("foo")));
    QVERIFY(!basicCompletions.contains(QLatin1String("m")));
    QVERIFY(basicCompletions.contains(QLatin1String("Foo")));
    QVERIFY(basicCompletions.contains(QLatin1String("func")));
    QVERIFY(basicCompletions.contains(QLatin1String("f")));

    test.insertText("f.");

    QStringList memberCompletions = test.getCompletions();
    QVERIFY(memberCompletions.contains(QLatin1String("foo")));
    QVERIFY(memberCompletions.contains(QLatin1String("m")));
    QVERIFY(!memberCompletions.contains(QLatin1String("func")));
    QVERIFY(!memberCompletions.contains(QLatin1String("f")));
}

void CppToolsPlugin::test_completion_template_1()
{
    const QByteArray source = "\n"
            "template <class T>\n"
            "class Foo\n"
            "{\n"
            "    typedef T Type;\n"
            "    T foo();\n"
            "    T m;\n"
            "};\n"
            "\n"
            "void func() {\n"
            "    Foo f;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "Foo::");

    const QStringList completions = test.getCompletions();
    QVERIFY(completions.contains(QLatin1String("Type")));
    QVERIFY(completions.contains(QLatin1String("foo")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(!completions.contains(QLatin1String("T")));
    QVERIFY(!completions.contains(QLatin1String("f")));
    QVERIFY(!completions.contains(QLatin1String("func")));
}

void CppToolsPlugin::test_completion_template_2()
{
    const QByteArray source = "\n"
            "template <class T>\n"
            "struct List\n"
            "{\n"
            "    T &at(int);\n"
            "};\n"
            "\n"
            "struct Tupple { int a; int b; };\n"
            "\n"
            "void func() {\n"
            "    List<Tupple> l;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "l.at(0).");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 3);
    QVERIFY(completions.contains(QLatin1String("Tupple")));
    QVERIFY(completions.contains(QLatin1String("a")));
    QVERIFY(completions.contains(QLatin1String("b")));
}

void CppToolsPlugin::test_completion_template_3()
{
    const QByteArray source = "\n"
            "template <class T>\n"
            "struct List\n"
            "{\n"
            "    T t;\n"
            "};\n"
            "\n"
            "struct Tupple { int a; int b; };\n"
            "\n"
            "void func() {\n"
            "    List<Tupple> l;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "l.t.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 3);
    QVERIFY(completions.contains(QLatin1String("Tupple")));
    QVERIFY(completions.contains(QLatin1String("a")));
    QVERIFY(completions.contains(QLatin1String("b")));
}

void CppToolsPlugin::test_completion_template_4()
{
    const QByteArray source = "\n"
            "template <class T>\n"
            "struct List\n"
            "{\n"
            "    typedef T U;\n"
            "    U u;\n"
            "};\n"
            "\n"
            "struct Tupple { int a; int b; };\n"
            "\n"
            "void func() {\n"
            "    List<Tupple> l;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "l.u.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 3);
    QVERIFY(completions.contains(QLatin1String("Tupple")));
    QVERIFY(completions.contains(QLatin1String("a")));
    QVERIFY(completions.contains(QLatin1String("b")));
}

void CppToolsPlugin::test_completion_template_5()
{
    const QByteArray source = "\n"
            "template <class T>\n"
            "struct List\n"
            "{\n"
            "    T u;\n"
            "};\n"
            "\n"
            "struct Tupple { int a; int b; };\n"
            "\n"
            "void func() {\n"
            "    typedef List<Tupple> LT;\n"
            "    LT l;"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "l.u.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 3);
    QVERIFY(completions.contains(QLatin1String("Tupple")));
    QVERIFY(completions.contains(QLatin1String("a")));
    QVERIFY(completions.contains(QLatin1String("b")));
}

void CppToolsPlugin::test_completion_template_6()
{
    const QByteArray source = "\n"
            "class Item\n"
            "{\n"
            "    int i;\n"
            "};\n"
            "\n"
            "template <typename T>\n"
            "class Container\n"
            "{\n"
            "    T get();\n"
            "};\n"
            "\n"
            "template <typename T> class Container;\n"
            "\n"
            "class ItemContainer: public Container<Item>\n"
            "{};\n"
            "ItemContainer container;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "container.get().");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Item")));
    QVERIFY(completions.contains(QLatin1String("i")));
}

void CppToolsPlugin::test_completion_template_7()
{
    const QByteArray source = "\n"
            "struct Test\n"
            "{\n"
            "   int i;\n"
            "};\n"
            "\n"
            "template<typename T>\n"
            "struct TemplateClass\n"
            "{\n"
            "    T* ptr;\n"
            "\n"
            "    typedef T element_type;\n"
            "    TemplateClass(T* t) : ptr(t) {}\n"
            "    element_type* operator->()\n"
            "    {\n"
            "        return ptr;\n"
            "    }\n"
            "};\n"
            "\n"
            "TemplateClass<Test> p(new Test);\n"
            "@\n"
            ;
    CompletionTestCase test(source, "p->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Test")));
    QVERIFY(completions.contains(QLatin1String("i")));
}

void CppToolsPlugin::test_completion_type_of_pointer_is_typedef()
{
    const QByteArray source = "\n"
            "typedef struct Foo\n"
            "{\n"
            "    int foo;\n"
            "} Foo;\n"
            "Foo *bar;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "bar->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("foo")));
}

void CppToolsPlugin::test_completion_instantiate_full_specialization()
{
    const QByteArray source = "\n"
            "template<typename T>\n"
            "struct Template\n"
            "{\n"
            "   int templateT_i;\n"
            "};\n"
            "\n"
            "template<>\n"
            "struct Template<char>\n"
            "{\n"
            "    int templateChar_i;\n"
            "};\n"
            "\n"
            "Template<char> templateChar;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "templateChar.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Template")));
    QVERIFY(completions.contains(QLatin1String("templateChar_i")));
}

void CppToolsPlugin::test_completion()
{
    QFETCH(QByteArray, code);
    QFETCH(QStringList, expectedCompletions);

    CompletionTestCase test(code, "c.");

    QStringList actualCompletions = test.getCompletions();
    actualCompletions.sort();
    expectedCompletions.sort();

    QCOMPARE(actualCompletions, expectedCompletions);
}

void CppToolsPlugin::test_completion_template_as_base()
{
    test_completion();
}

void CppToolsPlugin::test_completion_template_as_base_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "class Data { int dataMember; };\n"
            "template <class T> class Other : public T { int otherMember; };\n"
            "\n"
            "void func() {\n"
            "    Other<Data> c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Other"));
    completions.append(QLatin1String("otherMember"));
    QTest::newRow("case: base as template directly") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "template <class T> class Other : public T { int otherMember; };\n"
            "template <class T> class More : public Other<T> { int moreMember; };\n"
            "\n"
            "void func() {\n"
            "    More<Data> c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Other"));
    completions.append(QLatin1String("otherMember"));
    completions.append(QLatin1String("More"));
    completions.append(QLatin1String("moreMember"));
    QTest::newRow("case: base as class template") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "template <class T> class Other : public T { int otherMember; };\n"
            "template <class T> class More : public ::Other<T> { int moreMember; };\n"
            "\n"
            "void func() {\n"
            "    More<Data> c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Other"));
    completions.append(QLatin1String("otherMember"));
    completions.append(QLatin1String("More"));
    completions.append(QLatin1String("moreMember"));
    QTest::newRow("case: base as globally qualified class template") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "namespace NS {\n"
            "template <class T> class Other : public T { int otherMember; };\n"
            "}\n"
            "template <class T> class More : public NS::Other<T> { int moreMember; };\n"
            "\n"
            "void func() {\n"
            "    More<Data> c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Other"));
    completions.append(QLatin1String("otherMember"));
    completions.append(QLatin1String("More"));
    completions.append(QLatin1String("moreMember"));
    QTest::newRow("case: base as namespace qualified class template") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "namespace NS {\n"
            "template <class T> class Delegate { typedef Data<T> Type; };\n"
            "}\n"
            "template <class T> class Final : public NS::Delegate<T>::Type { int finalMember; };\n"
            "\n"
            "void func() {\n"
            "    Final<Data> c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Final"));
    completions.append(QLatin1String("finalMember"));
    QTest::newRow("case: base as nested template name") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "namespace NS {\n"
            "template <class T> class Delegate { typedef Data<T> Type; };\n"
            "}\n"
            "class Final : public NS::Delegate<Data>::Type { int finalMember; };\n"
            "\n"
            "void func() {\n"
            "    Final c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Final"));
    completions.append(QLatin1String("finalMember"));
    QTest::newRow("case: base as nested template name in non-template") << code << completions;

    completions.clear();
    code = "\n"
            "class Data { int dataMember; };\n"
            "namespace NS {\n"
            "template <class T> class Other : public T { int otherMember; };\n"
            "}\n"
            "class Final : public NS::Other<Data> { int finalMember; };\n"
            "\n"
            "void func() {\n"
            "    Final c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}";
    completions.append(QLatin1String("Data"));
    completions.append(QLatin1String("dataMember"));
    completions.append(QLatin1String("Final"));
    completions.append(QLatin1String("finalMember"));
    completions.append(QLatin1String("Other"));
    completions.append(QLatin1String("otherMember"));
    QTest::newRow("case: base as template name in non-template") << code << completions;
}

void CppToolsPlugin::test_completion_use_global_identifier_as_base_class()
{
    test_completion();
}

void CppToolsPlugin::test_completion_use_global_identifier_as_base_class_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "struct Global\n"
            "{\n"
            "    int int_global;\n"
            "};\n"
            "\n"
            "struct Final : ::Global\n"
            "{\n"
            "   int int_final;\n"
            "};\n"
            "\n"
            "Final c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_global"));
    completions.append(QLatin1String("int_final"));
    completions.append(QLatin1String("Final"));
    completions.append(QLatin1String("Global"));
    QTest::newRow("case: derived as global and base as global") << code << completions;

    completions.clear();

    code = "\n"
            "struct Global\n"
            "{\n"
            "    int int_global;\n"
            "};\n"
            "\n"
            "namespace NS\n"
            "{\n"
            "struct Final : ::Global\n"
            "{\n"
            "   int int_final;\n"
            "};\n"
            "}\n"
            "\n"
            "NS::Final c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_global"));
    completions.append(QLatin1String("int_final"));
    completions.append(QLatin1String("Final"));
    completions.append(QLatin1String("Global"));
    QTest::newRow("case: derived is inside namespace, base as global")
            << code << completions;

    completions.clear();

    // This test does not work due to the bug QTCREATORBUG-7912
//    code = "\n"
//            "struct Global\n"
//            "{\n"
//            "    int int_global;\n"
//            "};\n"
//            "\n"
//            "template <typename T>\n"
//            "struct Enclosing\n"
//            "{\n"
//            "struct Final : ::Global\n"
//            "{\n"
//            "   int int_final;\n"
//            "};\n"
//            "}\n"
//            "\n"
//            "Enclosing<int>::Final c;\n"
//            "@\n"
//            "// padding so we get the scope right\n";

//    completions.append(QLatin1String("int_global"));
//    completions.append(QLatin1String("int_final"));
//    completions.append(QLatin1String("Final"));
//    completions.append(QLatin1String("Global"));
//    QTest::newRow("case: derived is enclosed by template, base as global")
//    << code << completions;

//    completions.clear();
}

void CppToolsPlugin::test_completion_base_class_has_name_the_same_as_derived()
{
    test_completion();
}

void CppToolsPlugin::test_completion_base_class_has_name_the_same_as_derived_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "struct A : A\n"
            "{\n"
            "   int int_a;\n"
            "};\n"
            "\n"
            "A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class is derived class") << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS\n"
            "{\n"
            "struct A : A\n"
            "{\n"
            "   int int_a;\n"
            "};\n"
            "}\n"
            "\n"
            "NS::A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class is derived class. class is in namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS\n"
            "{\n"
            "struct A : NS::A\n"
            "{\n"
            "   int int_a;\n"
            "};\n"
            "}\n"
            "\n"
            "NS::A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class is derived class. class is in namespace. "
                  "use scope operator for base class") << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS1\n"
            "{\n"
            "struct A\n"
            "{\n"
            "   int int_ns1_a;\n"
            "};\n"
            "}\n"
            "namespace NS2\n"
            "{\n"
            "struct A : NS1::A\n"
            "{\n"
            "   int int_ns2_a;\n"
            "};\n"
            "}\n"
            "\n"
            "NS2::A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_ns1_a"));
    completions.append(QLatin1String("int_ns2_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class has the same name as derived but in different namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "struct Enclosing\n"
            "{\n"
            "struct A\n"
            "{\n"
            "   int int_enclosing_a;\n"
            "};\n"
            "};\n"
            "namespace NS2\n"
            "{\n"
            "struct A : Enclosing::A\n"
            "{\n"
            "   int int_ns2_a;\n"
            "};\n"
            "}\n"
            "\n"
            "NS2::A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_enclosing_a"));
    completions.append(QLatin1String("int_ns2_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class has the same name as derived(in namespace) "
                  "but is nested by different class") << code << completions;

    completions.clear();

    code = "\n"
            "struct EnclosingBase\n"
            "{\n"
            "struct A\n"
            "{\n"
            "   int int_enclosing_base_a;\n"
            "};\n"
            "};\n"
            "struct EnclosingDerived\n"
            "{\n"
            "struct A : EnclosingBase::A\n"
            "{\n"
            "   int int_enclosing_derived_a;\n"
            "};\n"
            "};\n"
            "\n"
            "EnclosingDerived::A c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_enclosing_base_a"));
    completions.append(QLatin1String("int_enclosing_derived_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class has the same name as derived(nested) "
                  "but is nested by different class") << code << completions;

    completions.clear();

    code = "\n"
            "template <typename T>\n"
            "struct A : A\n"
            "{\n"
            "   int int_a;\n"
            "};\n"
            "\n"
            "A<int> c;\n"
            "@\n"
            "// padding so we get the scope right\n";

    completions.append(QLatin1String("int_a"));
    completions.append(QLatin1String("A"));
    QTest::newRow("case: base class is derived class. class is a template")
            << code << completions;

    completions.clear();
}

void CppToolsPlugin::test_completion_cyclic_inheritance()
{
    test_completion();
}

void CppToolsPlugin::test_completion_cyclic_inheritance_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "struct B;\n"
            "struct A : B { int _a; };\n"
            "struct B : A { int _b; };\n"
            "\n"
            "A c;\n"
            "@\n"
            ;
    completions.append(QLatin1String("A"));
    completions.append(QLatin1String("_a"));
    completions.append(QLatin1String("B"));
    completions.append(QLatin1String("_b"));
    QTest::newRow("case: direct cyclic inheritance") << code << completions;

    completions.clear();
    code = "\n"
            "struct C;\n"
            "struct A : C { int _a; };\n"
            "struct B : A { int _b; };\n"
            "struct C : B { int _c; };\n"
            "\n"
            "A c;\n"
            "@\n"
            ;
    completions.append(QLatin1String("A"));
    completions.append(QLatin1String("_a"));
    completions.append(QLatin1String("B"));
    completions.append(QLatin1String("_b"));
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("_c"));
    QTest::newRow("case: indirect cyclic inheritance") << code << completions;

    completions.clear();
    code = "\n"
            "struct B;\n"
            "struct A : B { int _a; };\n"
            "struct C { int _c; };\n"
            "struct B : C, A { int _b; };\n"
            "\n"
            "A c;\n"
            "@\n"
            ;
    completions.append(QLatin1String("A"));
    completions.append(QLatin1String("_a"));
    completions.append(QLatin1String("B"));
    completions.append(QLatin1String("_b"));
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("_c"));
    QTest::newRow("case: indirect cyclic inheritance") << code << completions;

    completions.clear();
    code = "\n"
            "template< typename T > struct C;\n"
            "template< typename T, typename S > struct D : C< S >\n"
            "{\n"
            "   T _d_t;\n"
            "   S _d_s;\n"
            "};\n"
            "template< typename T > struct C : D< T, int >\n"
            "{\n"
            "   T _c_t;\n"
            "};\n"
            "\n"
            "D<int, float> c;\n"
            "@\n"
            ;
    completions.append(QLatin1String("D"));
    completions.append(QLatin1String("_d_t"));
    completions.append(QLatin1String("_d_s"));
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("_c_t"));
    QTest::newRow("case: direct cyclic inheritance with templates")
            << code << completions;

    completions.clear();
    code = "\n"
            "template< typename T > struct C;\n"
            "template< typename T, typename S > struct D : C< S >\n"
            "{\n"
            "   T _d_t;\n"
            "   S _d_s;\n"
            "};\n"
            "template< typename T > struct B : D< T, int >\n"
            "{\n"
            "   T _b_t;\n"
            "};\n"
            "template< typename T > struct C : B<T>\n"
            "{\n"
            "   T _c_t;\n"
            "};\n"
            "\n"
            "D<int, float> c;\n"
            "@\n"
            ;
    completions.append(QLatin1String("D"));
    completions.append(QLatin1String("_d_t"));
    completions.append(QLatin1String("_d_s"));
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("_c_t"));
    completions.append(QLatin1String("B"));
    completions.append(QLatin1String("_b_t"));
    QTest::newRow("case: indirect cyclic inheritance with templates")
            << code << completions;

    completions.clear();
    code = "\n"
           "namespace NS\n"
           "{\n"
           "template <typename T> struct SuperClass\n"
           "{\n"
           "    typedef T Type;\n"
           "    Type super_class_type;\n"
           "};\n"
           "}\n"
           "\n"
           "template <typename T>\n"
           "struct Class;\n"
           "\n"
           "template <typename T, typename S>\n"
           "struct ClassRecurse : Class<S>\n"
           "{\n"
           "    T class_recurse_t;\n"
           "    S class_recurse_s;\n"
           "};\n"
           "\n"
           "template <typename T>\n"
           "struct Class : ClassRecurse< T, typename ::NS::SuperClass<T>::Type >\n"
           "{\n"
           "    T class_t;\n"
           "};\n"
           "\n"
           "Class<int> c;\n"
           "@\n"
            ;
    completions.append(QLatin1String("Class"));
    completions.append(QLatin1String("ClassRecurse"));
    completions.append(QLatin1String("class_t"));
    completions.append(QLatin1String("class_recurse_s"));
    completions.append(QLatin1String("class_recurse_t"));
    QTest::newRow("case: direct cyclic inheritance with templates, more complex situation")
            << code << completions;
}

void CppToolsPlugin::test_completion_template_function()
{
    QFETCH(QByteArray, code);
    QFETCH(QStringList, expectedCompletions);

    CompletionTestCase test(code);

    QStringList actualCompletions = test.getCompletions();
    actualCompletions.sort();
    expectedCompletions.sort();

    QString errorPattern(QLatin1String("Completion not found: %1"));
    foreach (const QString &completion, expectedCompletions) {
        QByteArray errorMessage = errorPattern.arg(completion).toUtf8();
        QVERIFY2(actualCompletions.contains(completion), errorMessage.data());
    }
}

void CppToolsPlugin::test_completion_template_function_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
           "template <class tclass, typename tname, int tint>\n"
           "tname Hello(const tclass &e)\n"
           "{\n"
           "    tname e2 = e;\n"
           "    @\n"
           "}";

    completions.append(QLatin1String("tclass"));
    completions.append(QLatin1String("tname"));
    completions.append(QLatin1String("tint"));
    QTest::newRow("case: template parameters in template function body")
            << code << completions;

    completions.clear();

    code = "\n"
           "template <class tclass, typename tname, int tint>\n"
           "tname Hello(const tclass &e, @)\n"
           "{\n"
           "    tname e2 = e;\n"
           "}";

    completions.append(QLatin1String("tclass"));
    completions.append(QLatin1String("tname"));
    completions.append(QLatin1String("tint"));
    QTest::newRow("case: template parameters in template function parameters list")
            << code << completions;
}

void CppToolsPlugin::test_completion_enclosing_template_class()
{
    test_completion();
}

void CppToolsPlugin::test_completion_enclosing_template_class_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "template<typename T>\n"
            "struct Enclosing\n"
            "{\n"
            "    struct Nested { int int_nested; }; \n"
            "    int int_enclosing;\n"
            "};\n"
            "\n"
            "Enclosing<int>::Nested c;"
            "@\n";
    completions.append(QLatin1String("Nested"));
    completions.append(QLatin1String("int_nested"));
    QTest::newRow("case: nested class with enclosing template class")
            << code << completions;

    completions.clear();

    code = "\n"
            "template<typename T>\n"
            "struct Enclosing\n"
            "{\n"
            "    template<typename T> struct Nested { int int_nested; }; \n"
            "    int int_enclosing;\n"
            "};\n"
            "\n"
            "Enclosing<int>::Nested<int> c;"
            "@\n";
    completions.append(QLatin1String("Nested"));
    completions.append(QLatin1String("int_nested"));
    QTest::newRow("case: nested template class with enclosing template class")
            << code << completions;
}

void CppToolsPlugin::test_completion_instantiate_nested_class_when_enclosing_is_template()
{
    const QByteArray source = "\n"
            "struct Foo \n"
            "{\n"
            "    int foo_i;\n"
            "};\n"
            "\n"
            "template <typename T>\n"
            "struct Enclosing\n"
            "{\n"
            "    struct Nested\n"
            "    {\n"
            "        T nested_t;\n"
            "    } nested;\n"
            "\n"
            "    T enclosing_t;\n"
            "};\n"
            "\n"
            "Enclosing<Foo> enclosing;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "enclosing.nested.nested_t.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("foo_i")));
}

void CppToolsPlugin::test_completion_instantiate_nested_of_nested_class_when_enclosing_is_template()
{
    const QByteArray source = "\n"
            "struct Foo \n"
            "{\n"
            "    int foo_i;\n"
            "};\n"
            "\n"
            "template <typename T>\n"
            "struct Enclosing\n"
            "{\n"
            "    struct Nested\n"
            "    {\n"
            "        T nested_t;\n"
            "        struct NestedNested\n"
            "        {\n"
            "            T nestedNested_t;\n"
            "        } nestedNested;\n"
            "    } nested;\n"
            "\n"
            "    T enclosing_t;\n"
            "};\n"
            "\n"
            "Enclosing<Foo> enclosing;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "enclosing.nested.nestedNested.nestedNested_t.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("foo_i")));
}

void CppToolsPlugin::test_completion_instantiate_template_with_default_argument_type()
{
    const QByteArray source = "\n"
            "struct Foo\n"
            "{\n"
            "    int bar;\n"
            "};\n"
            "\n"
            "template <typename T = Foo>\n"
            "struct Template\n"
            "{\n"
            "    T t;\n"
            "};\n"
            "\n"
            "Template<> templateWithDefaultTypeOfArgument;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "templateWithDefaultTypeOfArgument.t.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_instantiate_template_with_default_argument_type_as_template()
{
    const QByteArray source = "\n"
            "struct Foo\n"
            "{\n"
            "    int bar;\n"
            "};\n"
            "\n"
            "template <typename T>\n"
            "struct TemplateArg\n"
            "{\n"
            "    T t;\n"
            "};\n"
            "template <typename T, typename S = TemplateArg<T> >\n"
            "struct Template\n"
            "{\n"
            "    S s;\n"
            "};\n"
            "\n"
            "Template<Foo> templateWithDefaultTypeOfArgument;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "templateWithDefaultTypeOfArgument.s.t.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_member_access_operator_1()
{
    const QByteArray source = "\n"
            "struct S { void t(); };\n"
            "void f() { S *s;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "s.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("t")));
    QVERIFY(replaceAccessOperator);
}

void CppToolsPlugin::test_completion_typedef_of_type_and_decl_of_type_no_replace_access_operator()
{
    const QByteArray source = "\n"
            "struct S { int m; };\n"
            "typedef S SType;\n"
            "SType p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(!replaceAccessOperator);
}

void CppToolsPlugin::test_completion_typedef_of_pointer_and_decl_of_pointer_no_replace_access_operator()
{
    const QByteArray source = "\n"
            "struct S { int m; };\n"
            "typedef S *SType;\n"
            "SType *p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 0);
    QVERIFY(!replaceAccessOperator);
}

void CppToolsPlugin::test_completion_typedef_of_type_and_decl_of_pointer_replace_access_operator()
{
    const QByteArray source = "\n"
            "struct S { int m; };\n"
            "typedef S SType;\n"
            "SType *p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(replaceAccessOperator);
}

void CppToolsPlugin::test_completion_typedef_of_pointer_and_decl_of_type_replace_access_operator()
{
    const QByteArray source = "\n"
            "struct S { int m; };\n"
            "typedef S* SPtr;\n"
            "SPtr p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(replaceAccessOperator);
}

void CppToolsPlugin::test_completion_predecl_typedef_of_type_and_decl_of_pointer_replace_access_operator()
{
    const QByteArray source = "\n"
            "typedef struct S SType;\n"
            "struct S { int m; };\n"
            "SType *p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(replaceAccessOperator);
}

void CppToolsPlugin::test_completion_predecl_typedef_of_type_and_decl_type_no_replace_access_operator()
{
    const QByteArray source = "\n"
            "typedef struct S SType;\n"
            "struct S { int m; };\n"
            "SType p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(!replaceAccessOperator);
}

void CppToolsPlugin::test_completion_predecl_typedef_of_pointer_and_decl_of_pointer_no_replace_access_operator()
{
    const QByteArray source = "\n"
            "typedef struct S *SType;\n"
            "struct S { int m; };\n"
            "SType *p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 0);
    QVERIFY(!replaceAccessOperator);
}

void CppToolsPlugin::test_completion_predecl_typedef_of_pointer_and_decl_of_type_replace_access_operator()
{
    const QByteArray source = "\n"
            "typedef struct S *SType;\n"
            "struct S { int m; };\n"
            "SType p;\n"
            "@\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p.");

    bool replaceAccessOperator = false;
    const QStringList completions = test.getCompletions(&replaceAccessOperator);
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("S")));
    QVERIFY(completions.contains(QLatin1String("m")));
    QVERIFY(replaceAccessOperator);
}

void CppToolsPlugin::test_completion_typedef_of_pointer()
{
    const QByteArray source = "\n"
            "struct Foo { int bar; };\n"
            "typedef Foo *FooPtr;\n"
            "void main()\n"
            "{\n"
            "   FooPtr ptr;\n"
            "   @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "ptr->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_typedef_of_pointer_inside_function()
{
    const QByteArray source = "\n"
            "struct Foo { int bar; };\n"
            "void f()\n"
            "{\n"
            "   typedef Foo *FooPtr;\n"
            "   FooPtr ptr;\n"
            "   @\n"
            "    // padding so we get the scope right\n"
            "}";
    CompletionTestCase test(source, "ptr->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_typedef_is_inside_function_before_declaration_block()
{
    const QByteArray source = "\n"
            "struct Foo { int bar; };\n"
            "void f()\n"
            "{\n"
            "   typedef Foo *FooPtr;\n"
            "   if (true) {\n"
            "       FooPtr ptr;\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }"
            "}"
            ;
    CompletionTestCase test(source, "ptr->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_resolve_complex_typedef_with_template()
{
    const QByteArray source = "\n"
            "template <typename T>\n"
            "struct Template2\n"
            "{\n"
            "    typedef typename T::template Template1<T>::TT TemplateTypedef;\n"
            "    TemplateTypedef templateTypedef;\n"
            "};\n"
            "struct Foo\n"
            "{\n"
            "    int bar;\n"
            "    template <typename T>\n"
            "    struct Template1\n"
            "    {\n"
            "        typedef T TT;\n"
            "    };\n"
            "};\n"
            "void fun()\n"
            "{\n"
            "    Template2<Foo> template2;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "template2.templateTypedef.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 3);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
    QVERIFY(completions.contains(QLatin1String("Template1")));
}

void CppToolsPlugin::test_completion_template_specialization_with_pointer()
{
    const QByteArray source = "\n"
            "template <typename T>\n"
            "struct Template\n"
            "{\n"
            "    T variable;\n"
            "};\n"
            "template <typename T>\n"
            "struct Template<T *>\n"
            "{\n"
            "    T *pointer;\n"
            "};\n"
            "Template<int*> templ;\n"
            "@\n"
            ;
    CompletionTestCase test(source, "templ.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Template")));
    QVERIFY(completions.contains(QLatin1String("pointer")));
}

void CppToolsPlugin::test_completion_typedef_using_templates1()
{
    const QByteArray source = "\n"
            "namespace NS1\n"
            "{\n"
            "template<typename T>\n"
            "struct NS1Struct\n"
            "{\n"
            "    typedef T *pointer;\n"
            "    pointer bar;\n"
            "};\n"
            "}\n"
            "namespace NS2\n"
            "{\n"
            "using NS1::NS1Struct;\n"
            "\n"
            "template <typename T>\n"
            "struct NS2Struct\n"
            "{\n"
            "    typedef NS1Struct<T> NS1StructTypedef;\n"
            "    typedef typename NS1StructTypedef::pointer pointer;\n"
            "    pointer p;\n"
            "};\n"
            "}\n"
            "struct Foo\n"
            "{\n"
            "    int bar;\n"
            "};\n"
            "void fun()\n"
            "{\n"
            "    NS2::NS2Struct<Foo> s;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "s.p->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_typedef_using_templates2()
{
    const QByteArray source = "\n"
            "namespace NS1\n"
            "{\n"
            "template<typename T>\n"
            "struct NS1Struct\n"
            "{\n"
            "    typedef T *pointer;\n"
            "    pointer bar;\n"
            "};\n"
            "}\n"
            "namespace NS2\n"
            "{\n"
            "using NS1::NS1Struct;\n"
            "\n"
            "template <typename T>\n"
            "struct NS2Struct\n"
            "{\n"
            "    typedef NS1Struct<T> NS1StructTypedef;\n"
            "    typedef typename NS1StructTypedef::pointer pointer;\n"
            "    pointer p;\n"
            "};\n"
            "}\n"
            "struct Foo\n"
            "{\n"
            "    int bar;\n"
            "};\n"
            "void fun()\n"
            "{\n"
            "    NS2::NS2Struct<Foo>::pointer p;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "p->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo")));
    QVERIFY(completions.contains(QLatin1String("bar")));
}

void CppToolsPlugin::test_completion_namespace_alias_with_many_namespace_declarations()
{
    const QByteArray source =
            "namespace NS1\n"
            "{\n"
            "namespace NS2\n"
            "{\n"
            "struct Foo1\n"
            "{\n"
            "    int bar1;\n"
            "};\n"
            "}\n"
            "}\n"
            "namespace NS1\n"
            "{\n"
            "namespace NS2\n"
            "{\n"
            "struct Foo2\n"
            "{\n"
            "    int bar2;\n"
            "};\n"
            "}\n"
            "}\n"
            "namespace NS = NS1::NS2;\n"
            "int main()\n"
            "{\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "NS::");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("Foo1")));
    QVERIFY(completions.contains(QLatin1String("Foo2")));
}

void CppToolsPlugin::test_completion_QTCREATORBUG9098()
{
    const QByteArray source =
            "template <typename T>\n"
            "class B\n"
            "{\n"
            "public:\n"
            "    C<T> c;\n"
            "};\n"
            "template <typename T>\n"
            "class A\n"
            "{\n"
            "public:\n"
            "    B<T> b;\n"
            "    void fun()\n"
            "    {\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "    }\n"
            "};\n"
            ;
    CompletionTestCase test(source, "b.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("c")));
    QVERIFY(completions.contains(QLatin1String("B")));
}

void CppToolsPlugin::test_completion_type_and_using_declaration()
{
    test_completion();
}

void CppToolsPlugin::test_completion_type_and_using_declaration_data()
{
    QTest::addColumn<QByteArray>("code");
    QTest::addColumn<QStringList>("expectedCompletions");

    QByteArray code;
    QStringList completions;

    code = "\n"
            "namespace NS\n"
            "{\n"
            "struct C { int m; };\n"
            "}\n"
            "void foo()\n"
            "{\n"
            "    using NS::C;\n"
            "    C c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type and using declaration inside function")
            << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS\n"
            "{\n"
            "struct C { int m; };\n"
            "}\n"
            "using NS::C;\n"
            "void foo()\n"
            "{\n"
            "    C c;\n"
            "    @\n"
            "    // padding so we get the scope right\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type and using declaration in global namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "struct C { int m; };\n"
            "namespace NS\n"
            "{\n"
            "   using ::C;\n"
            "   void foo()\n"
            "   {\n"
            "       C c;\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type in global namespace and using declaration in NS namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "struct C { int m; };\n"
            "namespace NS\n"
            "{\n"
            "   void foo()\n"
            "   {\n"
            "       using ::C;\n"
            "       C c;\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type in global namespace and using declaration inside function in NS namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS1\n"
            "{\n"
            "struct C { int m; };\n"
            "}\n"
            "namespace NS2\n"
            "{\n"
            "   void foo()\n"
            "   {\n"
            "       using NS1::C;\n"
            "       C c;\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type inside namespace NS1 and using declaration in function inside NS2 namespace")
            << code << completions;

    completions.clear();

    code = "\n"
            "namespace NS1\n"
            "{\n"
            "struct C { int m; };\n"
            "}\n"
            "namespace NS2\n"
            "{\n"
            "   using NS1::C;\n"
            "   void foo()\n"
            "   {\n"
            "       C c;\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }\n"
            "}\n";
    completions.append(QLatin1String("C"));
    completions.append(QLatin1String("m"));
    QTest::newRow("case: type inside namespace NS1 and using declaration inside NS2 namespace")
            << code << completions;
}

void CppToolsPlugin::test_completion_instantiate_template_with_anonymous_class()
{
    const QByteArray source =
            "template <typename T>\n"
            "struct S\n"
            "{\n"
            "    union { int i; char c; };\n"
            "};\n"
            "void fun()\n"
            "{\n"
            "   S<int> s;\n"
            "   @\n"
            "   // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "s.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 1);
    QVERIFY(completions.contains(QLatin1String("S")));
}

void CppToolsPlugin::test_completion_instantiate_template_function()
{
    const QByteArray source =
            "template <typename T>\n"
            "T* templateFunction() { return 0; }\n"
            "struct A { int a; };\n"
            "void foo()\n"
            "{\n"
            "   @\n"
            "   // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "templateFunction<A>()->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 2);
    QVERIFY(completions.contains(QLatin1String("A")));
    QVERIFY(completions.contains(QLatin1String("a")));
}

void CppToolsPlugin::test_completion_crash_cloning_template_class_QTCREATORBUG9329()
{
    const QByteArray source =
            "struct A {};\n"
            "template <typename T>\n"
            "struct Templ {};\n"
            "struct B : A, Templ<A>\n"
            "{\n"
            "   int f()\n"
            "   {\n"
            "       @\n"
            "       // padding so we get the scope right\n"
            "   }\n"
            "};\n"
            ;
    CompletionTestCase test(source, "this->");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 4);
    QVERIFY(completions.contains(QLatin1String("A")));
    QVERIFY(completions.contains(QLatin1String("B")));
    QVERIFY(completions.contains(QLatin1String("Templ")));
    QVERIFY(completions.contains(QLatin1String("f")));
}

void CppToolsPlugin::test_completion_recursive_auto_declarations1_QTCREATORBUG9503()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    auto object2 = object1;\n"
            "    auto object1 = object2;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "object1.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_auto_declarations2_QTCREATORBUG9503()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    auto object3 = object1;\n"
            "    auto object2 = object3;\n"
            "    auto object1 = object2;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "object1.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_typedefs_declarations1()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    typedef A B;\n"
            "    typedef B A;\n"
            "    A a;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "a.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_typedefs_declarations2()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    typedef A C;\n"
            "    typedef C B;\n"
            "    typedef B A;\n"
            "    A a;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "a.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_using_declarations1()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    using B = A;\n"
            "    using A = B;\n"
            "    A a;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "a.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_using_declarations2()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    using C = A;\n"
            "    using B = C;\n"
            "    using A = B;\n"
            "    A a;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "a.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_recursive_using_typedef_declarations()
{
    const QByteArray source =
            "void f()\n"
            "{\n"
            "    using B = A;\n"
            "    typedef B A;\n"
            "    A a;\n"
            "    @;\n"
            "    // padding so we get the scope right\n"
            "}\n"
            ;
    CompletionTestCase test(source, "a.");

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 0);
}

void CppToolsPlugin::test_completion_signals_hide_QPrivateSignal()
{
    const QByteArray source =
        "#define SIGNAL(a) #a\n"
        "#define SLOT(a) #a\n"
        "#define signals public\n"
        "#define Q_OBJECT struct QPrivateSignal {};\n"
        "\n"
        "class QObject\n"
        "{\n"
        "public:\n"
        "    void connect(QObject *, char *, QObject *, char *);\n"
        "};\n"
        "\n"
        "class Timer : public QObject\n"
        "{\n"
        "    Q_OBJECT\n"
        "signals:\n"
        "    void timeout(QPrivateSignal);\n"
        "};\n"
        "\n"
        "void client()\n"
        "{\n"
        "    Timer *timer = new Timer;\n"
        "    connect(timer, SIGNAL(@\n"
        "}\n";
    CompletionTestCase test(source);

    const QStringList completions = test.getCompletions();
    QCOMPARE(completions.size(), 1);
    QVERIFY(completions.contains(QLatin1String("timeout()")));
}
