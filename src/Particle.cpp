#include "Particle.h"

#include <QDebug>

Particle::Particle()
{
	qDebug() << "Particle constructor";
}

Particle::~Particle()
{
	qDebug() << "Particle destructor";
}

void Particle::draw()
{
	qDebug() << "Particle::draw()";
}
