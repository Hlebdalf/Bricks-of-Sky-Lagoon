// Fill out your copyright notice in the Description page of Project Settings.


#include "CPDA_PartsData.h"

UStaticMesh* UCPDA_PartsData::GetPart(FString name)
{
	for (UStaticMesh* Part : PartsArray)
	{
		if (Part->GetName() == name)
		{
			return Part;
		}
	}
	return nullptr;
}