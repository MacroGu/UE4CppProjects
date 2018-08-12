// Fill out your copyright notice in the Description page of Project Settings.

#include "SlAiHandObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "Engine/StaticMesh.h"
#include "Components/BoxComponent.h"


// Sets default values
ASlAiHandObject::ASlAiHandObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// ʵ���������
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	// ������̬ģ��
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionProfileName(FName("NoCollision"));

	// ʵ������ײ���
	AffectionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("AffectCollision"));
	AffectionCollision->SetupAttachment(RootComponent);
	AffectionCollision->SetCollisionProfileName(FName("ToolProfile"));


	// ��ʼ���ر�Overlay ���
	AffectionCollision->SetGenerateOverlapEvents(false);

	// �󶨼�ⷽ������ײ��
	FScriptDelegate OverlayBegin;
	OverlayBegin.BindUFunction(this, "OnOverlayBegin");
	AffectionCollision->OnComponentBeginOverlap.Add(OverlayBegin);

	FScriptDelegate OverlayEnd;
	OverlayEnd.BindUFunction(this, "OnOverlayEnd");
	AffectionCollision->OnComponentEndOverlap.Add(OverlayEnd);


}

// Called when the game starts or when spawned
void ASlAiHandObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlAiHandObject::OnOverlayBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

}

void ASlAiHandObject::OnOverlayEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ASlAiHandObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

