#ifndef THREADED_PROCESSOR_H
#define THREADED_PROCESSOR_H

#include <QThread>
#include "Generator.h"
#include "TriangleMesh.h"

class ThreadedProcessor : public QThread
{
	public:
		void run();
};

#endif
