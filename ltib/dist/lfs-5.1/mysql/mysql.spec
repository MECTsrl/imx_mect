%define pfx /opt/freescale/rootfs/%{_target_cpu}

Summary         : MySQL SQL database, client programs and shared library
Name            : mysql
Version         : 4.1.12
Release         : 0
License         : GPL
Vendor          : Freescale
Packager        : Jason Jin
Group           : System Environment/Daemons
BuildRoot       : %{_tmppath}/%{name}
Prefix          : %{pfx}
AutoReqProv     : no


%Package rfs
Summary         : Trimmed mysql for root file system requirements.
Vendor          : MECT s.r.l.
Packager        : Mihai Lazarescu
Group           : System Environment/Daemons
AutoReqProv     : no


%Description rfs
mysql package contents restricted to just the files that are
needed at run time on the target.


%Description
%{summary}


%Prep
export LC_ALL
LC_ALL=C

%setup -T -c -n %{name}
cd ..; rmdir %{name}; ln -s ../../../projects/%{name} %{name}


%Build
export LC_ALL
LC_ALL=C

# Timestamp order is important.
for f in configure.ac configure.in aclocal.m4 configure config.h.in Makefile.am Makefile.in; do
	find . -name $f -exec touch {} \;
done
./configure \
	--prefix=/usr \
	--host=$CFGHOST \
	--build=%{_build} \
	--enable-so \
	--with-named-curses-libs=-lncurses \
	--without-man \
	--without-docs \
	ac_cv_sys_restartable_syscalls=${ac_cv_sys_restartable_syscalls='no'} \
	ac_cv_conv_longlong_to_float=yes \
	--with-zlib	
find . -name errmsg.sys -print0 | xargs -0 touch

make -j$(nproc)


%Install
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT%{pfx}%{_prefix}
make install prefix=$RPM_BUILD_ROOT%{pfx}%{_prefix}

mv $RPM_BUILD_ROOT%{pfx}%{_prefix}/lib/mysql/* $RPM_BUILD_ROOT%{pfx}%{_prefix}/lib
rmdir $RPM_BUILD_ROOT%{pfx}%{_prefix}/lib/mysql


%Clean
export LC_ALL
LC_ALL=C

rm -rf $RPM_BUILD_ROOT


%Files
%defattr(-,root,root)
%{pfx}/*

%Files rfs
%defattr(-,root,root)
%{pfx}/usr/bin/comp_err
%{pfx}/usr/bin/isamchk
%{pfx}/usr/bin/isamlog
%{pfx}/usr/bin/make_win_binary_distribution
%{pfx}/usr/bin/make_win_src_distribution
%{pfx}/usr/bin/msql2mysql
%{pfx}/usr/bin/my_print_defaults
%{pfx}/usr/bin/myisam_ftdump
%{pfx}/usr/bin/myisamchk
%{pfx}/usr/bin/myisamlog
%{pfx}/usr/bin/myisampack
%{pfx}/usr/bin/mysql
%{pfx}/usr/bin/mysql_client_test
%{pfx}/usr/bin/mysql_config
%{pfx}/usr/bin/mysql_convert_table_format
%{pfx}/usr/bin/mysql_create_system_tables
%{pfx}/usr/bin/mysql_explain_log
%{pfx}/usr/bin/mysql_find_rows
%{pfx}/usr/bin/mysql_fix_extensions
%{pfx}/usr/bin/mysql_fix_privilege_tables
%{pfx}/usr/bin/mysql_install_db
%{pfx}/usr/bin/mysql_secure_installation
%{pfx}/usr/bin/mysql_setpermission
%{pfx}/usr/bin/mysql_tableinfo
%{pfx}/usr/bin/mysql_tzinfo_to_sql
%{pfx}/usr/bin/mysql_waitpid
%{pfx}/usr/bin/mysql_zap
%{pfx}/usr/bin/mysqlaccess
%{pfx}/usr/bin/mysqladmin
%{pfx}/usr/bin/mysqlbinlog
%{pfx}/usr/bin/mysqlbug
%{pfx}/usr/bin/mysqlcheck
%{pfx}/usr/bin/mysqld_multi
%{pfx}/usr/bin/mysqld_safe
%{pfx}/usr/bin/mysqldump
%{pfx}/usr/bin/mysqldumpslow
%{pfx}/usr/bin/mysqlhotcopy
%{pfx}/usr/bin/mysqlimport
%{pfx}/usr/bin/mysqlmanager-pwgen
%{pfx}/usr/bin/mysqlmanagerc
%{pfx}/usr/bin/mysqlshow
%{pfx}/usr/bin/mysqltest
%{pfx}/usr/bin/pack_isam
%{pfx}/usr/bin/perror
%{pfx}/usr/bin/replace
%{pfx}/usr/bin/resolve_stack_dump
%{pfx}/usr/bin/resolveip
%{pfx}/usr/lib/libmysqlclient.so
%{pfx}/usr/lib/libmysqlclient.so.14
%{pfx}/usr/lib/libmysqlclient.so.14.0.0
%{pfx}/usr/libexec/mysqld
%{pfx}/usr/share/mysql/Description.plist
%{pfx}/usr/share/mysql/Info.plist
%{pfx}/usr/share/mysql/MySQL-shared-compat.spec
%{pfx}/usr/share/mysql/StartupParameters.plist
%{pfx}/usr/share/mysql/charsets/Index.xml
%{pfx}/usr/share/mysql/charsets/README
%{pfx}/usr/share/mysql/charsets/armscii8.xml
%{pfx}/usr/share/mysql/charsets/ascii.xml
%{pfx}/usr/share/mysql/charsets/cp1250.xml
%{pfx}/usr/share/mysql/charsets/cp1251.xml
%{pfx}/usr/share/mysql/charsets/cp1256.xml
%{pfx}/usr/share/mysql/charsets/cp1257.xml
%{pfx}/usr/share/mysql/charsets/cp850.xml
%{pfx}/usr/share/mysql/charsets/cp852.xml
%{pfx}/usr/share/mysql/charsets/cp866.xml
%{pfx}/usr/share/mysql/charsets/dec8.xml
%{pfx}/usr/share/mysql/charsets/geostd8.xml
%{pfx}/usr/share/mysql/charsets/greek.xml
%{pfx}/usr/share/mysql/charsets/hebrew.xml
%{pfx}/usr/share/mysql/charsets/hp8.xml
%{pfx}/usr/share/mysql/charsets/keybcs2.xml
%{pfx}/usr/share/mysql/charsets/koi8r.xml
%{pfx}/usr/share/mysql/charsets/koi8u.xml
%{pfx}/usr/share/mysql/charsets/latin1.xml
%{pfx}/usr/share/mysql/charsets/latin2.xml
%{pfx}/usr/share/mysql/charsets/latin5.xml
%{pfx}/usr/share/mysql/charsets/latin7.xml
%{pfx}/usr/share/mysql/charsets/macce.xml
%{pfx}/usr/share/mysql/charsets/macroman.xml
%{pfx}/usr/share/mysql/charsets/swe7.xml
%{pfx}/usr/share/mysql/czech/errmsg.sys
%{pfx}/usr/share/mysql/czech/errmsg.txt
%{pfx}/usr/share/mysql/danish/errmsg.sys
%{pfx}/usr/share/mysql/danish/errmsg.txt
%{pfx}/usr/share/mysql/dutch/errmsg.sys
%{pfx}/usr/share/mysql/dutch/errmsg.txt
%{pfx}/usr/share/mysql/english/errmsg.sys
%{pfx}/usr/share/mysql/english/errmsg.txt
%{pfx}/usr/share/mysql/estonian/errmsg.sys
%{pfx}/usr/share/mysql/estonian/errmsg.txt
%{pfx}/usr/share/mysql/fill_help_tables.sql
%{pfx}/usr/share/mysql/french/errmsg.sys
%{pfx}/usr/share/mysql/french/errmsg.txt
%{pfx}/usr/share/mysql/german/errmsg.sys
%{pfx}/usr/share/mysql/german/errmsg.txt
%{pfx}/usr/share/mysql/greek/errmsg.sys
%{pfx}/usr/share/mysql/greek/errmsg.txt
%{pfx}/usr/share/mysql/hungarian/errmsg.sys
%{pfx}/usr/share/mysql/hungarian/errmsg.txt
%{pfx}/usr/share/mysql/italian/errmsg.sys
%{pfx}/usr/share/mysql/italian/errmsg.txt
%{pfx}/usr/share/mysql/japanese-sjis/errmsg.sys
%{pfx}/usr/share/mysql/japanese-sjis/errmsg.txt
%{pfx}/usr/share/mysql/japanese/errmsg.sys
%{pfx}/usr/share/mysql/japanese/errmsg.txt
%{pfx}/usr/share/mysql/korean/errmsg.sys
%{pfx}/usr/share/mysql/korean/errmsg.txt
%{pfx}/usr/share/mysql/mi_test_all
%{pfx}/usr/share/mysql/mi_test_all.res
%{pfx}/usr/share/mysql/my-huge.cnf
%{pfx}/usr/share/mysql/my-innodb-heavy-4G.cnf
%{pfx}/usr/share/mysql/my-large.cnf
%{pfx}/usr/share/mysql/my-medium.cnf
%{pfx}/usr/share/mysql/my-small.cnf
%{pfx}/usr/share/mysql/mysql-4.1.12.spec
%{pfx}/usr/share/mysql/mysql-log-rotate
%{pfx}/usr/share/mysql/mysql.server
%{pfx}/usr/share/mysql/mysql_fix_privilege_tables.sql
%{pfx}/usr/share/mysql/ndb-config-2-node.ini
%{pfx}/usr/share/mysql/norwegian-ny/errmsg.sys
%{pfx}/usr/share/mysql/norwegian-ny/errmsg.txt
%{pfx}/usr/share/mysql/norwegian/errmsg.sys
%{pfx}/usr/share/mysql/norwegian/errmsg.txt
%{pfx}/usr/share/mysql/polish/errmsg.sys
%{pfx}/usr/share/mysql/polish/errmsg.txt
%{pfx}/usr/share/mysql/portuguese/errmsg.sys
%{pfx}/usr/share/mysql/portuguese/errmsg.txt
%{pfx}/usr/share/mysql/postinstall
%{pfx}/usr/share/mysql/preinstall
%{pfx}/usr/share/mysql/romanian/errmsg.sys
%{pfx}/usr/share/mysql/romanian/errmsg.txt
%{pfx}/usr/share/mysql/russian/errmsg.sys
%{pfx}/usr/share/mysql/russian/errmsg.txt
%{pfx}/usr/share/mysql/serbian/errmsg.sys
%{pfx}/usr/share/mysql/serbian/errmsg.txt
%{pfx}/usr/share/mysql/slovak/errmsg.sys
%{pfx}/usr/share/mysql/slovak/errmsg.txt
%{pfx}/usr/share/mysql/spanish/errmsg.sys
%{pfx}/usr/share/mysql/spanish/errmsg.txt
%{pfx}/usr/share/mysql/swedish/errmsg.sys
%{pfx}/usr/share/mysql/swedish/errmsg.txt
%{pfx}/usr/share/mysql/ukrainian/errmsg.sys
%{pfx}/usr/share/mysql/ukrainian/errmsg.txt
