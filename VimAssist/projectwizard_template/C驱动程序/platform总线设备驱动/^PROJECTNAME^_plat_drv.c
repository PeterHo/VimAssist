#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>

#include "common.h"

static int ^PROJECTNAME^_plat_drv_probe(struct platform_device *dev)
{
    PLOG("^PROJECTNAME^_plat_drv_probe %s\n", dev_name(&dev->dev));
    return 0;
}

static int ^PROJECTNAME^_plat_drv_remove(struct platform_device *dev)
{
    PLOG("^PROJECTNAME^_plat_drv_remove %s\n", dev_name(&dev->dev));
    return 0;
}

struct platform_driver ^PROJECTNAME^_plat_drv = 
{
    .probe     = ^PROJECTNAME^_plat_drv_probe,
    .remove    = ^PROJECTNAME^_plat_drv_remove,
    .driver    = 
    {
        .owner = THIS_MODULE,
        .name  = DEVICE_NAME,
    }
};

static int __init ^PROJECTNAME^_plat_drv_init(void)
{
    int ret = 0;
	PLOG("^PROJECTNAME^_plat_dev Init\n");
    ret = platform_driver_register(&^PROJECTNAME^_plat_drv);
	return ret;
}

static void __exit ^PROJECTNAME^_plat_drv_cleanup(void)
{
	PLOG("^PROJECTNAME^_plat_dev Cleanup\n");
    platform_driver_unregister(&^PROJECTNAME^_plat_drv);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_plat_drv_init);
module_exit(^PROJECTNAME^_plat_drv_cleanup);
