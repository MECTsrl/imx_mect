/**
 * @file
 * @author Emiliano Bergamaschini <ebergamaschini@mect.it>
 *
 * @section LICENSE
 * Copyright Mect s.r.l. 2013
 *
 * @brief Generic page
 */
#include "app_logprint.h"
#include "atcmplugin.h"
#include "main.h"
#include "%ClassName%.h"
#include "ui_%ClassName%.h"
#include "crosstable.h"

/**
 * @brief this macro is used to set the %ClassName:u% style.
 * the syntax is html stylesheet-like
 */
#define SET_%ClassName:u%_STYLE() { \
	QString mystyle; \
	mystyle.append(this->styleSheet()); \
	/* add there the page stilesheet customization */ \
	mystyle.append(""); \
	this->setStyleSheet(mystyle); \
}

/**
 * @brief This is the constructor. The operation written here, are executed only one time: at the instantiation of the page.
 */
%ClassName%::%ClassName%(QWidget *parent) :
	page(parent),
	ui(new Ui::%ClassName%)
{
	ui->setupUi(this);
	/* set here the protection level (pwd_admin_e, pwd_super_user_e, pwd_user_e, pwd_operator_e), default is pwd_operator_e
	 * protection_level = pwd_operator_e;
	 */

	/* set up the page style */
	//SET_PAGE_STYLE();
	/* set the style described into the macro SET_%ClassName:u%_STYLE */
	SET_%ClassName:u%_STYLE();
	translateFontSize(this);
}

/**
 * @brief This is the reload member. The operation written here, are executed every time this page is shown.
 */
void %ClassName%::reload()
{
	/*
	   H variables initalizations:
	     variableList.clear();
	     variableList << "VARIABLE1" << "VARIABLE2" << "VARIABLE3"
	   alarm banner initialization in QLineEdit:
	     rotateShowError(ui->myLineEdit, ERROR_LABEL_PERIOD_MS);
	 */
}

/**
 * @brief This is the updateData member. The operation written here, are executed every REFRESH_MS milliseconds.
 */
void %ClassName%::updateData()
{
	if (this->isVisible() == false)
	{
		return;
	}
	/* call the parent updateData member */
	page::updateData();
	
	/* To read the cross table variable UINT TEST1:
	 *    uint_16 tmp = TEST1;
	 */
	/* To write 5 into the the cross table variable UINT TEST1:
	 *    doWrite_TEST1(5);
	 */	
}

/**
 * @brief This is the event slot to detect new language translation.
 */
void %ClassName%::changeEvent(QEvent * event)
{
    if (event->type() == QEvent::LanguageChange)
    {
        ui->retranslateUi(this);
    }
}

/**
 * @brief This is the distructor member. The operation written here, are executed only one time when the page will be deleted.
 */
%ClassName%::~%ClassName%()
{
	delete ui;
}
