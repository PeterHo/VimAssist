#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>

#include "common.h"

static struct platform_device *^PROJECTNAME^_plat_dev;
static struct resource res[] = 
{
    [0] = 
    {
        .start = IRQ_EINT(0),
        .end   = IRQ_EINT(0),
        .flags = IORESOURCE_IRQ,
    },
    [1] = 
    {
        .start = IRQ_EINT(1),
        .end   = IRQ_EINT(1),
        .flags = IORESOURCE_IRQ,
    },
};

static int __init ^PROJECTNAME^_plat_dev_init(void)
{
	PLOG("^PROJECTNAME^_plat_dev Init\n");
    ^PROJECTNAME^_plat_dev = platform_device_alloc(DEVICE_NAME, -1);
    platform_device_add_resources(^PROJECTNAME^_plat_dev, res, sizeof(res)/sizeof(struct resource));
    platform_device_add(^PROJECTNAME^_plat_dev);
	return 0;
}

static void __exit ^PROJECTNAME^_plat_dev_cleanup(void)
{
	PLOG("^PROJECTNAME^_plat_dev Cleanup\n");
    platform_device_unregister(^PROJECTNAME^_plat_dev);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_plat_dev_init);
module_exit(^PROJECTNAME^_plat_dev_cleanup);
