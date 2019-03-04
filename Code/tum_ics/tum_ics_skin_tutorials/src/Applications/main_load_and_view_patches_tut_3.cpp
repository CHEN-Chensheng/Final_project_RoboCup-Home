#include <tum_ics_skin_descr/Patch/TfMarkerDataPatches.h>

#include <QApplication>
#include <QDebug>
#include <QVector>
#include <QFileInfo>
#include <QDir>

using namespace tum_ics_skin_descr;


int main( int argc, char** argv )
{
    ros::init(argc, argv, "load_and_view_patches_tut_fiad",
              ros::init_options::AnonymousName);
    ros::NodeHandle n;
    ros::Rate r(30);

    QApplication a(argc, argv);

    //    for(int i=0; i<argc; i++)
    //    {
    //        qDebug("%s",argv[i]);
    //    }

    if(argc != 2)
    {
        qCritical("Invalid number of arguments: %d",argc);
        return -1;
    }

    QString configFilePath = QString(argv[1]);
    QFileInfo fi(configFilePath);
    if(!fi.absoluteDir().exists())
    {
        qCritical("Invalid path '%s'",configFilePath.toAscii().data());
        return -1;
    }

    //////////////////////////////// Wrist patches init/////////////////////////////////////////
    Patch::TfMarkerDataPatches tfPatchesWrist;

    if(!tfPatchesWrist.loadFromParam(configFilePath,"~wrist_patch_list"))
    {
        return -1;
    }
    tfPatchesWrist.createDataConnections();
    tfPatchesWrist.enableDataConnctions();

    for(int i=0; i<tfPatchesWrist.numberOfPatches(); i++)
    {
        Patch::TfMarkerDataPatch* p = tfPatchesWrist.patch(i);
        qDebug("%s",p->briefInfo().toAscii().data());
        p->setLedColor(Skin::LedColor::Blue);
    }

    //////////////////////////////// Left Finger patches init//////////////////////////////////////
    Patch::TfMarkerDataPatches tfPatchesLF;

    if(!tfPatchesLF.loadFromParam(configFilePath,"~left_finger_patch_list"))
    {
        return -1;
    }
    tfPatchesLF.createDataConnections();
    tfPatchesLF.enableDataConnctions();

    for(int i=0; i<tfPatchesLF.numberOfPatches(); i++)
    {
        Patch::TfMarkerDataPatch* p = tfPatchesLF.patch(i);
        qDebug("%s",p->briefInfo().toAscii().data());
        p->setLedColor(Skin::LedColor::Blue);
    }

    /////////////////////////////// Right Finger patches init/////////////////////////////////////////
    Patch::TfMarkerDataPatches tfPatchesRF;

    if(!tfPatchesRF.loadFromParam(configFilePath,"~right_finger_patch_list"))
    {
        return -1;
    }
    tfPatchesRF.createDataConnections();
    tfPatchesRF.enableDataConnctions();

    for(int i=0; i<tfPatchesRF.numberOfPatches(); i++)
    {
        Patch::TfMarkerDataPatch* p = tfPatchesRF.patch(i);
        qDebug("%s",p->briefInfo().toAscii().data());
        p->setLedColor(Skin::LedColor::Blue);


    }

    while(ros::ok())
    {
        tfPatchesWrist.publish(ros::Duration(1.0));

        tfPatchesLF.publish(ros::Duration(1.0));

        tfPatchesRF.publish(ros::Duration(1.0));


        QApplication::processEvents();
        ros::spinOnce();
        r.sleep();
    }

    qDebug("exit");

    return 0;
}
