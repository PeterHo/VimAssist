#include <linux/module.h>
#include <linux/init.h>
#include "^PROJECTNAME^.h"

static int __init ^PROJECTNAME^_init(void)
{
	PLOG("Init\n");
	return 0;
}

static void __exit ^PROJECTNAME^_cleanup(void)
{
	PLOG("Cleanup\n");
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_init);
module_exit(^PROJECTNAME^_cleanup);
