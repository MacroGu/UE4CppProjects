// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiCourse.h"
#include "Modules/ModuleManager.h"
#include "SlAiStyle.h"



void SlAiCourseModule::StartupModule()
{
	// ��ʼ��ʽ��
	FSlateStyleRegistry::UnRegisterSlateStyle(SlAiStyle::GetStyleSetName());
	SlAiStyle::Initialize();

}

void SlAiCourseModule::ShutdownModule()
{
	SlAiStyle::ShutDown();
}


IMPLEMENT_PRIMARY_GAME_MODULE(SlAiCourseModule, SlAiCourse, "SlAiCourse");
