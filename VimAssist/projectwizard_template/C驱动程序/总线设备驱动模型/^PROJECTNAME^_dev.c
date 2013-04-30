#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "common.h"

extern struct bus_type ^PROJECTNAME^_bus;
extern struct device ^PROJECTNAME^_bus_dev;

void ^PROJECTNAME^_dev_release(struct device *dev)
{
    PLOG("^PROJECTNAME^_dev_release\n");
}

ssize_t ^PROJECTNAME^_dev_show(struct device *dev, struct device_attribute *attr, char *buf)
{
    return sprintf(buf, "%s\n", "This is ^PROJECTNAME^ device!");
}

struct device ^PROJECTNAME^_dev = 
{
    .parent = &^PROJECTNAME^_bus_dev,
    .bus = &^PROJECTNAME^_bus,
    .release = ^PROJECTNAME^_dev_release,
};

static DEVICE_ATTR(version, S_IRUGO, ^PROJECTNAME^_dev_show, NULL);

static int __init ^PROJECTNAME^_dev_init(void)
{
    int ret = 0;

	PLOG("^PROJECTNAME^_dev Init\n");
    dev_set_name(&^PROJECTNAME^_dev, "^PROJECTNAME^_dev");
    ret = device_register(&^PROJECTNAME^_dev);
    if ( ret ) 
    {
        return ret;
    }
    ret = device_create_file(&^PROJECTNAME^_dev, &dev_attr_version);
	return ret;
}

static void __exit ^PROJECTNAME^_dev_cleanup(void)
{
	PLOG("^PROJECTNAME^_dev Cleanup\n");
    device_remove_file(&^PROJECTNAME^_dev, &dev_attr_version);
    device_unregister(&^PROJECTNAME^_dev);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_dev_init);
module_exit(^PROJECTNAME^_dev_cleanup);
