#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{
	public:
		Particle();
		~Particle();
		
		void compile();
		void draw();
	
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_xrot;
		float m_yrot;
		float m_zrot;
};

#endif
