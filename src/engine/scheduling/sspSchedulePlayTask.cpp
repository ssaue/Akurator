/*
  ==============================================================================

    sspSchedulePlayTask.cpp
    Created: 31 Jan 2019 11:15:53am
    Author:  sigurds

  ==============================================================================
*/

#include "sspSchedulePlayTask.h"

sspSchedulePlayTask::sspSchedulePlayTask()
	: task_()
{
}

sspSchedulePlayTask::sspSchedulePlayTask(std::weak_ptr<sspPlayTask> task, double seconds)
	: task_(task), seconds_(seconds)
{
}

void sspSchedulePlayTask::setTask(std::weak_ptr<sspPlayTask> task, double seconds)
{
	task_ = task;
	seconds_ = seconds;
}
