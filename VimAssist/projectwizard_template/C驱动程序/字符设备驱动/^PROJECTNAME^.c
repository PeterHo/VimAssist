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

#include <asm/uaccess.h>
#include "^PROJECTNAME^.h"

static int ^PROJECTNAME^_major = ^CPROJECTNAME^_MAJOR;
module_param(^PROJECTNAME^_major, int, S_IRUGO);

struct ^PROJECTNAME^_dev *^PROJECTNAME^_devp; /*设备结构体指针*/
struct cdev cdev; 
struct class *^PROJECTNAME^_class;

/*
 * 文件打开函数
 * */
int ^PROJECTNAME^_open(struct inode *inode, struct file *filp)
{
    struct ^PROJECTNAME^_dev *dev;
    /*获取次设备号*/
    int num = MINOR(inode->i_rdev);

    if (num >= ^CPROJECTNAME^_NR_DEVS) 
        return -ENODEV;
    dev = &^PROJECTNAME^_devp[num];
    /*将设备描述结构指针赋值给文件私有数据指针*/
    filp->private_data = dev;

    return 0; 
}

/*
 * 文件释放函数
 * */
int ^PROJECTNAME^_release(struct inode *inode, struct file *filp)
{
    return 0;
}

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
    unsigned long p =  *ppos;
    unsigned int count = size;
    int ret = 0;
    struct ^PROJECTNAME^_dev *dev = filp->private_data; /*获得设备结构体指针*/

    while ( !dev->canRead ) 
    {
        if ( filp->f_flags & O_NONBLOCK ) 
        {
            return -EAGAIN;
        }

        wait_event_interruptible(dev->rwq, dev->canRead);
    }

    if ( down_interruptible(&dev->sem) ) 
    {
        return -ERESTARTSYS;
    }

    /*判断读位置是否有效*/
    if (p >= ^CPROJECTNAME^_SIZE)
        return 0;
    if (count > ^CPROJECTNAME^_SIZE - p)
        count = ^CPROJECTNAME^_SIZE - p;

    /*读数据到用户空间*/
    if (copy_to_user(buf, (void*)(dev->data + p), count))
    {
        ret =  - EFAULT;
    }
    else
    {
        *ppos += count;
        ret = count;
        PLOG("read %d bytes(s) from %ld\n", count, p);
    }

    if ( ret ) 
    {
        dev->canWrite = true;
        wake_up(&(dev->wwq));
    }

    up(&dev->sem);

    return ret;
}

/*
 * 写函数
 */
static ssize_t ^PROJECTNAME^_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{
    unsigned long p =  *ppos;
    unsigned int count = size;
    int ret = 0;
    struct ^PROJECTNAME^_dev *dev = filp->private_data; /*获得设备结构体指针*/

    while ( !dev->canWrite ) 
    {
        if ( filp->f_flags & O_NONBLOCK ) 
        {
            return -EAGAIN;
        }

        wait_event_interruptible(dev->wwq, dev->canWrite);
    }
    
    if ( down_interruptible(&dev->sem) ) 
    {
        return -ERESTARTSYS;
    }

    /*分析和获取有效的写长度*/
    if (p >= ^CPROJECTNAME^_SIZE)
        return 0;
    if (count > ^CPROJECTNAME^_SIZE - p)
        count = ^CPROJECTNAME^_SIZE - p;

    /*从用户空间写入数据*/
    if (copy_from_user(dev->data + p, buf, count))
        ret =  - EFAULT;
    else {
        *ppos += count;
        ret = count;

        PLOG("written %d bytes(s) from %ld\n", count, p);
    }

    if ( ret ) 
    {
        dev->canRead = true;
        wake_up(&(dev->rwq));
    }

    up(&dev->sem);

    return ret;
}

/* 
 * seek文件定位函数 
 * */
static loff_t ^PROJECTNAME^_llseek(struct file *filp, loff_t offset, int whence)
{ 
    loff_t newpos;

    switch(whence) {
        case 0: /* SEEK_SET */
            newpos = offset;
            break;
        case 1: /* SEEK_CUR */
            newpos = filp->f_pos + offset;
            break;
        case 2: /* SEEK_END */
            newpos = ^CPROJECTNAME^_SIZE -1 + offset;
            break;
        default: /* can't happen */
            return -EINVAL;
    }
    if ((newpos<0) || (newpos>^CPROJECTNAME^_SIZE))
        return -EINVAL;
    filp->f_pos = newpos;
    return newpos;
}

/*
 * POLL
 * */
static unsigned int ^PROJECTNAME^_poll(struct file *filp, poll_table *wait)
{
    struct ^PROJECTNAME^_dev *dev = filp->private_data;
    unsigned int mask = 0;

    poll_wait(filp, &dev->rwq, wait);
    poll_wait(filp, &dev->wwq, wait);

    if ( dev->canRead ) 
    {
        mask |= POLLIN | POLLRDNORM;
    }
   
    if ( dev->canWrite ) 
    {
        mask |= POLLOUT | POLLWRNORM;
    }

    return mask;
}

/*
 * mmap
 * */
static int ^PROJECTNAME^_mmap(struct file *filp, struct vm_area_struct *vma)
{
    struct ^PROJECTNAME^_dev *dev = filp->private_data;
    unsigned long pfn = (unsigned long)(virt_to_phys(dev->data)>>PAGE_SHIFT);
    unsigned long size = (unsigned long)(vma->vm_end - vma->vm_start);

    if ( remap_pfn_range(vma, vma->vm_start, pfn, size, vma->vm_page_prot) ) 
    {
        return -EAGAIN;
    }

    return 0;
}

/*
 * 文件操作结构体
 * */
static const struct file_operations ^PROJECTNAME^_fops =
{
    .owner = THIS_MODULE,
    .open = ^PROJECTNAME^_open,
    .read = ^PROJECTNAME^_read,
    .write = ^PROJECTNAME^_write,
    .llseek = ^PROJECTNAME^_llseek,
    .unlocked_ioctl = ^PROJECTNAME^_ioctl,
    .poll = ^PROJECTNAME^_poll,
    .mmap = ^PROJECTNAME^_mmap,
    .release = ^PROJECTNAME^_release,
};

/*设备驱动模块加载函数*/
static int ^PROJECTNAME^_init(void)
{
    int result;
    int i;

    dev_t devno = MKDEV(^PROJECTNAME^_major, 0);
    /* 静态申请设备号*/
    if (^PROJECTNAME^_major)
        result = register_chrdev_region(devno, ^CPROJECTNAME^_NR_DEVS, "^PROJECTNAME^");
    else { /* 动态分配设备号 */ 
        result = alloc_chrdev_region(&devno, 0, ^CPROJECTNAME^_NR_DEVS, "^PROJECTNAME^");
        ^PROJECTNAME^_major = MAJOR(devno);
    }  

    if (result < 0)
        return result;

    /*初始化cdev结构*/
    cdev_init(&cdev, &^PROJECTNAME^_fops);
    cdev.owner = THIS_MODULE;

    /* 注册字符设备 */
    cdev_add(&cdev, MKDEV(^PROJECTNAME^_major, 0), ^CPROJECTNAME^_NR_DEVS);

    /* 为设备描述结构分配内存*/
    ^PROJECTNAME^_devp = kmalloc(^CPROJECTNAME^_NR_DEVS * sizeof(struct ^PROJECTNAME^_dev), GFP_KERNEL);
    if (!^PROJECTNAME^_devp)    /*申请失败*/
    {
        result =  - ENOMEM;
        goto fail_malloc;
    }
    memset(^PROJECTNAME^_devp, 0, sizeof(struct ^PROJECTNAME^_dev));

    ^PROJECTNAME^_class = class_create(THIS_MODULE, "^PROJECTNAME^_class");

    /*为设备分配内存*/
    for (i=0; i < ^CPROJECTNAME^_NR_DEVS; i++) 
    {
        ^PROJECTNAME^_devp[i].size = ^CPROJECTNAME^_SIZE;
        ^PROJECTNAME^_devp[i].data = kmalloc(^CPROJECTNAME^_SIZE, GFP_KERNEL);
        memset(^PROJECTNAME^_devp[i].data, 0, ^CPROJECTNAME^_SIZE);
        //ini wait queue
        ^PROJECTNAME^_devp[i].canRead = false;
        ^PROJECTNAME^_devp[i].canWrite = true;
        init_waitqueue_head(&^PROJECTNAME^_devp[i].rwq);
        init_waitqueue_head(&^PROJECTNAME^_devp[i].wwq);
        //ini sem
        sema_init(&^PROJECTNAME^_devp[i].sem, 1);

        device_create(^PROJECTNAME^_class, NULL, MKDEV(^PROJECTNAME^_major, i), NULL, "^PROJECTNAME^%d", i);
    }
    return 0;

fail_malloc: 
    unregister_chrdev_region(devno, 1);

    return result;
}

/*模块卸载函数*/
static void ^PROJECTNAME^_exit(void)
{
    int i;
    for ( i = 0; i < ^CPROJECTNAME^_NR_DEVS; ++i )
    {
        kfree(^PROJECTNAME^_devp[i].data);
        device_destroy(^PROJECTNAME^_class, MKDEV(^PROJECTNAME^_major, i));
    }
    
    cdev_del(&cdev);   /*注销设备*/
    class_destroy(^PROJECTNAME^_class);
    kfree(^PROJECTNAME^_devp);     /*释放设备结构体内存*/
    unregister_chrdev_region(MKDEV(^PROJECTNAME^_major, 0), ^CPROJECTNAME^_NR_DEVS); /*释放设备号*/
}

MODULE_AUTHOR("Macinsh");
MODULE_LICENSE("GPL");

module_init(^PROJECTNAME^_init);
module_exit(^PROJECTNAME^_exit);
