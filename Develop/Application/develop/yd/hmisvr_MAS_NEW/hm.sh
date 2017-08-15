#!  /bin/sh
make distclean
/usr/local/Trolltech/Qte-4.8.4-arm/bin/qmake
#/usr/local/Trolltech/QtEmbedded-4.8.4-arm/bin/qmake
make -j 8
cp hmisvr /home/rejulink/nfs/
cp hmisvr /mnt/hgfs/share_for_linux/

