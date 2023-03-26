// Fill out your copyright notice in the Description page of Project Settings.
#pragma once
#include "Async/AsyncWork.h"
#include "Multithreaded.h"
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MultithreadedLibrary.generated.h"

class MultithreadedTask : public FNonAbandonableTask {
public:
	MultithreadedTask(UObject* object) { this->object = object; }
	UObject* object;
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(MultithreadedTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork()
	{
		IMultithreaded::Execute_MultithreadedFunction(object);
	}
};

class CalculateMeshDataTask : public FNonAbandonableTask {
public:
	CalculateMeshDataTask(UObject* object) { this->object = object; }
	UObject* object;
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(CalculateMeshDataTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork()
	{
		IMultithreaded::Execute_CalculateMeshDataFunction(object);
	}
};

class CalculateMeshDecorationsTask : public FNonAbandonableTask {
public:
	CalculateMeshDecorationsTask(UObject* object) { this->object = object; }
	UObject* object;
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(CalculateMeshDecorationsTask, STATGROUP_ThreadPoolAsyncTasks);
	}
	void DoWork()
	{
		IMultithreaded::Execute_CalculateMeshDecorationsFunction(object);
	}
};

UCLASS()
class HEXADVENTURE_API UMultithreadedLibrary : public UBlueprintFunctionLibrary {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		static void CallMultithreadedFunction(UObject* object) {
		(new FAutoDeleteAsyncTask<MultithreadedTask>(object))->StartBackgroundTask();
	}
	UFUNCTION(BlueprintCallable)
		static void CallCalculateMeshData(UObject* object) {
		(new FAutoDeleteAsyncTask<CalculateMeshDataTask>(object))->StartBackgroundTask();
	}
	UFUNCTION(BlueprintCallable)
		static void CallCalculateMeshDecorations(UObject* object) {
		(new FAutoDeleteAsyncTask<CalculateMeshDecorationsTask>(object))->StartBackgroundTask();
	}
};