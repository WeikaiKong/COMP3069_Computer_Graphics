#pragma once

#include <stdio.h>
#include <glm/glm/glm.hpp>
#include "camera.h"

float cam_dist = 2.f;

// MoveAndOrientCamera: press a key to move the obj.
// cam: camera
// target: focus of the camera
// distance: distance from the camera to the target
// xoffset, yoffset: amount to move the camera
// implementation: 1) update camera yaw and pitch
// 2) calcualate the position on the imaginary sphere
// 3) update the front, right and up vectors
void MoveAndOrientCamera(SCamera& in, glm::vec3 target, float distance, float xoffset, float yoffset)
{
    in.Yaw -= xoffset * in.MovementSpeed;
    in.Pitch -= yoffset * in.MovementSpeed;

    if (in.Pitch > 89.0f)  in.Pitch = 89.f;
    if (in.Pitch < -89.0f) in.Pitch = -89.f;

    // calculate position
    in.Position = target + glm::vec3(glm::cos(glm::radians(in.Pitch)) * glm::sin(glm::radians(in.Yaw)) * cam_dist,
        glm::sin(glm::radians(in.Pitch)) * cam_dist,
        glm::cos(glm::radians(in.Pitch)) * glm::cos(glm::radians(in.Yaw)) * cam_dist);

    in.Front = glm::normalize(target - in.Position);
    in.Right = glm::normalize(glm::cross(in.Front, in.WorldUp));
    in.Up = glm::normalize(glm::cross(in.Right, in.Front));
}
