# Simple Digital Earth

#### 介绍

- 基于MFC和osgEarth的简单数字地球，包括加载OSG模型，加载高程图、地形图、局部纹理。

- 虽然编码都由本人完成，但是特别感谢OSG中文社区，中文社区提供的各种资源让我快速入门了OSG。

- 仓库中只提供了代码，其他文件和数据可在 **安装教程** 中的链接中找到。

#### 软件架构
- 最重要的类是COSGObject，用于加载模型，操作图层、视角，并获取视角坐标、人的坐标，反馈到界面上。

- 地球的加载主要依靠`DigitalMap.earth`文件，它用xml的形式定义了各个图层，我们在代码中利用ImageLayer等类操作图层。图层的来源有`.shp`、`.tif`等多种形式的文件。

- 除了`DigitalMap.earth`，国旗、动物等实体没有定义在`.earth`中，而是使用了命名空间`osgDB`中的函数来分别读取`.png`、`.osg`文件，将其作为OSG节点，并设置光照、坐标变换。


#### 安装教程

1. 下载程序压缩包 （服务器流量吃紧，有事联系ztz20001117@126.com），若提示不安全是因为网站还没开通SSL证书，强制保留即可，或复制链接去下载器下载。

2. 解压后有三个文件夹：DigitalEarth、OSG、osgEarth，**解压路径不要有中文！！！！！** MFC应用对中文路径可能不是太友好。

3. 在系统搜索菜单中搜索 **编辑系统环境变量** ，打开后点击 **环境变量**，在系统变量中选中 **PATH**，再点击 **编辑**。若没有搜索功能可自行搜索如何添加环境变量。

![输入图片说明](guide_pic%E6%90%9C%E7%B4%A2%E7%BC%96%E8%BE%91%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F.png)

![输入图片说明](guide_pic%E7%82%B9%E5%87%BB%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F.png)

![输入图片说明](guide_pic%E7%BC%96%E8%BE%91Path.png)

4. 在编辑环境变量的界面，点击 **新建** ，写入OSG、osgEarth文件夹中的bin目录及其子目录osgPlugin-3.6.5的路径，比如我的OSG中bin文件夹的路径为`D:\Environment\OSG\OSG\bin`，我就新建环境变量加入`D:\Environment\OSG\OSG\bin`，同理加入`D:\Environment\OSG\OSG\bin\osgPlugins-3.6.5`、`D:\Environment\OSG\osgEarth\bin`、`D:\Environment\OSG\osgEarth\bin\osgPlugins-3.6.5`，这些路径。点文件资源管理器上方的文件夹图标就能复制路径，一共要加 **四个路径！！！！** 。

![输入图片说明](guide_pic%E6%B7%BB%E5%8A%A0%E7%8E%AF%E5%A2%83%E5%8F%98%E9%87%8F.png)  

![输入图片说明](guide_pic%E7%9B%AE%E5%BD%95.png)  

5. 添加好环境变量后一路确定。然后按键盘`WIN+R`，输入`cmd`，在弹出的命令行窗口中依次输入两个命令`osgversion`和`osgearth_version`，若输出和图中一样，则说明配置成功； **如果不一样就重启电脑，再次打开命令行窗口输入命令，一般重启后就会好** 。

![输入图片说明](guide_pic%E7%A1%AE%E5%AE%9A1.png)

![输入图片说明](guide_pic%E7%A1%AE%E5%AE%9A2.png)

![输入图片说明](guide_pic%E7%A1%AE%E5%AE%9A3.png)

![输入图片说明](guide_pic%E8%BE%93%E5%85%A5cmd.png)

![输入图片说明](guide_pic%E7%A1%AE%E8%AE%A4%E9%85%8D%E7%BD%AE%E5%AE%8C%E6%88%90.png)

6. 打开DigitalEarth文件夹，双击DigitalEarth.exe就可，文件夹里的东西 **不要乱动**。

#### 使用说明

- 在视图区打钩可设置图层是否可见。

- 等高线在西藏与印度接壤处一块黑色的地方，放大可看到等高线。

![输入图片说明](guide_pic%E7%AD%89%E9%AB%98%E7%BA%BF%E4%BD%8D%E7%BD%AE.png)

- 局部高清图在浙江省，在浙江省德清县尤为高清，若找不到德清县，直接点击**野外考查-->前往**，就能到德清县附近，那里会有一头牛。等高线的位置也是局部高清图。

![输入图片说明](guide_pic%E6%B5%99%E6%B1%9F%E4%BD%8D%E7%BD%AE.png)

- 在飞行输入位置信息可快速到达那个位置，经度范围-180~180，纬度范围-90-90， **输入超出这个范围程序可能崩溃** 。

- 刚打开可能有点卡，等一段时间就好。
