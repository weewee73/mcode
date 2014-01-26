#!/bin/bash

##  1. 删除redhat原有的yum 
echo "remove redhat yum..."
rpm -aq | grep yum | xargs rpm -e --nodeps 


##  2. 下载yum安装文件 
##     http://mirrors.163.com/centos/6/os/i386/Packages/
##         python-iniparse-0.3.1-2.1.el6.noarch.rpm
##         yum-3.2.29-40.el6.centos.noarch.rpm
##         yum-metadata-parser-1.1.2-16.el6.i686.rpm
##         yum-plugin-fastestmirror-1.1.30-14.el6.noarch.rpm

url_dir="http://mirrors.163.com/centos/6/os/i386/Packages"

rpm_python="python-iniparse-0.3.1-2.1.el6.noarch.rpm"
rpm_metadata="yum-metadata-parser-1.1.2-16.el6.i686.rpm"
rpm_yum="yum-3.2.29-40.el6.centos.noarch.rpm"
rpm_plugin="yum-plugin-fastestmirror-1.1.30-14.el6.noarch.rpm"

wget $url_dir/$rpm_python $url_dir/$rpm_yum $url_dir/$rpm_metadata $url_dir/$rpm_plugin 

##   3. 安装yum 
rpm -ivh $rpm_python
rpm -ivh $rpm_metadata
rpm -ivh $rpm_yum $rpm_plugin
##      注意最后两个包必需同时安装，否则会相互依赖 

##   4. 更新yum源
cd /etc/yum.repos.d/ 
[[ -d bakup ]] || mkdir bakup
\mv * bakup 2>/dev/null
wget  http://mirrors.163.com/.help/CentOS6-Base-163.repo 

sed -i 's/\$releasever/6/g' CentOS6-Base-163.repo
##     把文件里面的$releasever全部替换为版本号，即6


##   5. 生成缓存
yum clean all
yum makecache

#yum install -y yum-downloadonly
#yum install -y --downloadonly --downloaddir=/root/test/ git{,web,-daemon,olite} httpd xinetd

##  安装EPEL第三方源
#rpm -ivh http://mirrors.ustc.edu.cn/fedora/epel/6/i386/epel-release-6-8.noarch.rpm
#rpm --import http://mirrors.163.com/centos/RPM-GPG-KEY-CentOS-6

