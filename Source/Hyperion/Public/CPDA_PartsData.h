// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CPDA_PartsData.generated.h"

/**
 * 
 */
UCLASS()
class HYPERION_API UCPDA_PartsData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	public:
    	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    	TArray<UStaticMesh *> PartsArray;
    	UFUNCTION(BlueprintPure)
    	UStaticMesh* GetPart(FString name);
	
};
