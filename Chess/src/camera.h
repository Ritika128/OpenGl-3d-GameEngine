#ifndef CAMERA_H
#define CAMERA_H
#define myPi 3.14159265359

#include "head.h"

class Camera                                            //  represents orbiting camera around center of coordinate system
{
public:
    glm::vec3 Position;                                 //  current position of camera

    int rotateAngle;                                    //  horizontal angle of camera rotation
    int tiltAngle;                                      //  vertical angle of camera rotation
    float distance;                                     //  distance of camera from center of orbit

 

    Camera()                                            //  one and only class constructor
    {
        setProperties();                                //  set default values of all properties

    }

    void setProperties(int _rotateAngle = 90, int _tiltAngle = 220, float _distance = 5.0f)     //  camera properties setter
    {
        
        rotateAngle = _rotateAngle;                     //  pass values from paramaters
        tiltAngle = _tiltAngle;
        distance = _distance;

        refreshPosition();                              //  update actual camera position
    }


    void refreshPosition()
    {                                                   //  calculate actual position of the camera
        Position.x = distance * -sinf(rotateAngle * (myPi / 180)) * cosf((tiltAngle) * (myPi / 180));
        Position.y = distance * -sinf((tiltAngle) * (myPi / 180));
        Position.z = -distance * cosf((rotateAngle) * (myPi / 180)) * cosf((tiltAngle) * (myPi / 180));
    }

    glm::mat4 loadViewMatrix()
    {                                                   //  use appropriate function to get view matrix
        return glm::lookAt(glm::vec3(Position.x, Position.y, Position.z), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }
};

#endif
