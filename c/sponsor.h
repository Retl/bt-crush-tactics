#ifndef SPONSOR_H
#define SPONSOR_H

//#include "temporarystatus.h"

typedef struct {
	char displayName[200];
    //Canons
    // Notoriety
	// TemporaryStatus tempStatuses[MAX_TEMP_STATUSES];
	//TemporaryStatus tempStatuses[10];
} Sponsor;

/*
ActiveObject initPlayer();

void aoAddStatus(ActiveObject *ao, TemporaryStatus tempStatus);

void aoRemoveStatus(ActiveObject *ao, enum TemporaryStatusType tst);

void aoRemoveStatusAtIndex(ActiveObject *ao, int ind);

void aoRefresh(ActiveObject *ao, TemporaryStatus tempStatus);

void aoInitStatuses(ActiveObject *ao);

void aoStep(ActiveObject *ao);

bool aoGetIndexOfStatus(ActiveObject *ao, enum TemporaryStatusType tst);

bool aoHasStatus(ActiveObject *ao, enum TemporaryStatusType tst);

void aoStepProcessTempStatuses(ActiveObject *ao);

*/
#endif