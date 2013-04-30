#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/mm.h>
#include <linux/device.h>
#include <linux/miscdevice.h>

#include <asm/uaccess.h>
#include "^PROJECTNAME^.h"

/*
 * IO control
 * */
long ^PROJECTNAME^_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
    int err = 0;
    int ret = 0;

    if ( _IOC_TYPE(cmd) != ^CPROJECTNAME^_IOC_MAGIC ) 
    {
        return -EINVAL;
    }
    if ( _IOC_NR(cmd) > ^CPROJECTNAME^_IOC_MAXNR ) 
    {
        return -EINVAL;
    }

    if ( _IOC_DIR(cmd) & _IOC_READ ) 
    {
        err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
    }
    else if ( _IOC_DIR(cmd) & _IOC_WRITE ) 
    {
        err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
    }
    if ( err ) 
    {
        return -EFAULT;
    }
    
    switch (cmd)
    {
    case ^CPROJECTNAME^_IOCPRINT:
        PLOG("^CPROJECTNAME^_IOCPRINT Done\n");
        break;
    case ^CPROJECTNAME^_IOCSETDATA:
        PLOG("^CPROJECTNAME^_IOCSETDATA Done\n");
        break;
    case ^CPROJECTNAME^_IOCGETDATA:
        PLOG("^CPROJECTNAME^_IOCGETDATA Done\n");
        break;

    default:
        return -EINVAL;
    }

    return ret;
}

/*
 * 读函数
 * */
static ssize_t ^PROJECTNAME^_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
    return 0;
}

/*
 * 文件操作结构体
 * */
static const struct file_operations ^PROJECTNAME^_fops =
{
    .owner = THIS_MODULE,
    .read = ^PROJECTNAME^_read,
    .unlocked_ioctl = ^PROJECTNAME^_ioctl,
};

static struct miscdevice miscdev = 
{
    .minor = MISC_DYNAMIC_MINOR,
    .name = DEVICE_NAME,
    .fops = &^PROJECTNAME^_fops,
};

/*设备驱动模块加载函数*/
static int ^PROJECTNAME^_init(void)
{
    int ret;
    ret = misc_register(&miscdev);

    return ret;
}

/*模块卸载函数*/
static void ^PROJECTNAME^_exit(void)
{
    misc_deregister(&miscdev);
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_init);
module_exit(^PROJECTNAME^_exit);
