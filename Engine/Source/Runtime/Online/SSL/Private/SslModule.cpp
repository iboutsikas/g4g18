// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SslPrivatePCH.h"

#include "SslCertificateManager.h"

DEFINE_LOG_CATEGORY(LogSsl);

// FHttpModule

IMPLEMENT_MODULE(FSslModule, SSL);

FSslModule* FSslModule::Singleton = NULL;

bool FSslModule::Exec(UWorld* InWorld, const TCHAR* Cmd, FOutputDevice& Ar)
{
	bool bResult = false;

	// Ignore any execs that don't start with HTTP
	if (FParse::Command(&Cmd, TEXT("SSL")))
	{
		bResult = false;
	}

	return bResult;
}

void FSslModule::StartupModule()
{	
	Singleton = this;

	CertificateManagerPtr = new FSslCertificateManager();
	static_cast<FSslCertificateManager*>(CertificateManagerPtr)->BuildRootCertificateArray();
}

void FSslModule::ShutdownModule()
{
	static_cast<FSslCertificateManager*>(CertificateManagerPtr)->EmptyRootCertificateArray();
	delete CertificateManagerPtr;

	Singleton = nullptr;
}

FSslModule& FSslModule::Get()
{
	if (Singleton == NULL)
	{
		check(IsInGameThread());
		FModuleManager::LoadModuleChecked<FSslModule>("SSL");
	}
	check(Singleton != NULL);
	return *Singleton;
}
