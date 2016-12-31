#ifndef H_UPGRADE
#define H_UPGRADE

/** \ingroup python
 * \file python/upgrade.h
 */

struct packageInfo {
    Header h;
    char selected;
    char * name;
    void * data;
} ;

struct pkgSet {
    struct packageInfo ** packages;
    int numPackages;
};

int ugFindUpgradePackages(struct pkgSet *psp, char *installRoot);

#endif
