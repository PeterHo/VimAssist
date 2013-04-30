#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "common.h"

static char *Version = "$Revision: 1.0 $";

static int ^PROJECTNAME^_bus_match(struct device *dev, struct device_driver *drv)
{
    return strcmp(dev_name(dev), drv->name)==0;
}

ssize_t ^PROJECTNAME^_bus_show_version(struct bus_type *bus, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "%s\n", Version);
}

static void ^PROJECTNAME^_bus_release(struct device *dev)
{
    PLOG("^PROJECTNAME^_bus_release\n");
}

struct device ^PROJECTNAME^_bus_dev = 
{
    .init_name = "^PROJECTNAME^_bus_dev",
    .release = ^PROJECTNAME^_bus_release,
};

struct bus_type ^PROJECTNAME^_bus = 
{
    .name = "^PROJECTNAME^_bus",
    .match = ^PROJECTNAME^_bus_match,
};

static BUS_ATTR(version, S_IRUGO, ^PROJECTNAME^_bus_show_version, NULL);

static int __init ^PROJECTNAME^_bus_init(void)
{
    int ret;

	PLOG("^PROJECTNAME^_bus Init\n");
    ret = bus_register(&^PROJECTNAME^_bus);
    if ( ret ) 
    {
        return ret;
    }
    if (bus_create_file(&^PROJECTNAME^_bus, &bus_attr_version))
    {
        PLOG("Fail to create version attribute\n");
    }
    ret = device_register(&^PROJECTNAME^_bus_dev);
    if ( ret ) 
    {
        PLOG("Fail to register device : ^PROJECTNAME^_bus\n");
    }
	return ret;
}

static void __exit ^PROJECTNAME^_bus_cleanup(void)
{
	PLOG("^PROJECTNAME^_bus Cleanup\n");
    device_unregister(&^PROJECTNAME^_bus_dev);
    bus_remove_file(&^PROJECTNAME^_bus, &bus_attr_version);
    bus_unregister(&^PROJECTNAME^_bus);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(^PROJECTNAME^_bus);
EXPORT_SYMBOL(^PROJECTNAME^_bus_dev);

module_init(^PROJECTNAME^_bus_init);
module_exit(^PROJECTNAME^_bus_cleanup);
