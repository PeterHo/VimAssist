#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "common.h"

extern struct bus_type ^PROJECTNAME^_bus;

static int ^PROJECTNAME^_drv_probe(struct device *dev)
{
    PLOG("^PROJECTNAME^_drv_probe %s\n", dev_name(dev));
    return 0;
}

static int ^PROJECTNAME^_drv_remove(struct device *dev)
{
    PLOG("^PROJECTNAME^_drv_remove %s\n", dev_name(dev));
    return 0;
}

static ssize_t ^PROJECTNAME^_drv_show(struct device_driver *drv, char *buf)
{
    return sprintf(buf, "%s\n", "^PROJECTNAME^_drv_show");
}

struct device_driver ^PROJECTNAME^_drv = 
{
    .name = "^PROJECTNAME^_dev",
    .bus = &^PROJECTNAME^_bus,
    .probe = ^PROJECTNAME^_drv_probe,
    .remove = ^PROJECTNAME^_drv_remove,
};

static DRIVER_ATTR(version, S_IRUGO, ^PROJECTNAME^_drv_show, NULL);

static int __init ^PROJECTNAME^_drv_init(void)
{
    int ret = 0;
	PLOG("^PROJECTNAME^_dev Init\n");
    ret = driver_register(&^PROJECTNAME^_drv);
    if ( ret ) 
    {
        return ret;
    }
    ret = driver_create_file(&^PROJECTNAME^_drv, &driver_attr_version);
	return ret;
}

static void __exit ^PROJECTNAME^_drv_cleanup(void)
{
	PLOG("^PROJECTNAME^_dev Cleanup\n");
    driver_remove_file(&^PROJECTNAME^_drv, &driver_attr_version);
    driver_unregister(&^PROJECTNAME^_drv);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_drv_init);
module_exit(^PROJECTNAME^_drv_cleanup);
