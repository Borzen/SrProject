#include "positionclass.h"

PositionClass::PositionClass()
{
	m_positionX = 0.0f;
	m_positionY = 0.0f;
	m_positionZ = 0.0f;
	
	m_rotationX = 0.0f;
	m_rotationY = 0.0f;
	m_rotationZ = 0.0f;

	m_frameTime = 0.0f;

	intPosY = -1;

	m_forwardSpeed   = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_upwardSpeed    = 0.0f;
	m_downwardSpeed  = 0.0f;
	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;

	m_X,m_Y,m_Z = 0.0f;

	isjumping = false;
	isFalling = false;
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::SetPosition(float x, float y, float z)
{
	m_positionX = x;
	m_positionY = y;
	m_positionZ = z;
	return;
}

void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotationX = x;
	m_rotationY = y;
	m_rotationZ = z;
	return;
}

void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_positionX;
	y = m_positionY;
	z = m_positionZ;
	return;
}

void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotationX;
	y = m_rotationY;
	z = m_rotationZ;
	return;
}

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}

void PositionClass::MoveForward(bool keydown)
{


	if(keydown && m_positionX+.25f < 256){
		m_positionX += .25f;
		m_positionZ += 0;
	}

	return;
}

void PositionClass::MoveBackward(bool keydown)
{
	if(keydown && (m_positionX-.25f >= 0)){
		m_positionX -= .25f;
		m_positionZ -= 0;
	}
	return;
}

void PositionClass::MoveUpward(bool keydown)
{
	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown && !isjumping)
	{
		isjumping = true;
		intPosY = m_positionY;
	}
	if(isjumping && intPosY >= 0){

		m_upwardSpeed += m_frameTime * 0.003f;

		if(m_upwardSpeed > (m_frameTime * 0.03f))
		{
			m_upwardSpeed = m_frameTime * 0.03f;
		}
	}
	if(!isFalling && m_positionY >= intPosY + 10){
		isjumping = false;
		isFalling = true;
	}
	// Update the height position.
	if(isjumping)
		m_positionY += m_upwardSpeed;

	return;
}

void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(isFalling)
	{
		m_downwardSpeed += m_frameTime * 0.003f;

		if(m_downwardSpeed > (m_frameTime * 0.03f))
		{
			m_downwardSpeed = m_frameTime * 0.03f;
		}
	}
	if(isFalling && m_positionY <= intPosY+1){
		isFalling = false;
		m_positionY = intPosY;
		intPosY = -1;
	}
	// Update the height position.
	if(isFalling && m_positionY > intPosY)
		m_positionY -= m_downwardSpeed;

	return;
}

void PositionClass::TurnLeft(bool keydown)
{
	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.01f;

		if(m_leftTurnSpeed > (m_frameTime * 0.15f))
		{
			m_leftTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_leftTurnSpeed -= m_frameTime* 0.005f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY -= m_leftTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY < 0.0f)
	{
		m_rotationY += 360.0f;
	}

	return;
}

void PositionClass::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightTurnSpeed += m_frameTime * 0.01f;

		if(m_rightTurnSpeed > (m_frameTime * 0.15f))
		{
			m_rightTurnSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_rightTurnSpeed -= m_frameTime* 0.005f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationY += m_rightTurnSpeed;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotationY > 360.0f)
	{
		m_rotationY -= 360.0f;
	}

	return;
}

void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f;

		if(m_lookUpSpeed > (m_frameTime * 0.15f))
		{
			m_lookUpSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookUpSpeed -= m_frameTime* 0.005f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX -= m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX > 90.0f)
	{
		m_rotationX = 90.0f;
	}

	return;
}

void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime * 0.01f;

		if(m_lookDownSpeed > (m_frameTime * 0.15f))
		{
			m_lookDownSpeed = m_frameTime * 0.15f;
		}
	}
	else
	{
		m_lookDownSpeed -= m_frameTime* 0.005f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotationX += m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	if(m_rotationX < -90.0f)
	{
		m_rotationX = -90.0f;
	}

	return;
}

bool PositionClass::GetFallState()
{
	return isFalling;
}

bool PositionClass::GetJumpState()
{
	return isjumping;
}

void PositionClass::SetRevert()
{
	m_X = m_positionX;
	m_Y = m_positionY;
	m_Z = m_positionZ;
}

void PositionClass::RevertPos()
{
	m_positionX = m_X;
	m_positionY = m_Y;
	m_positionZ = m_Z;
	if(isFalling)
	{
		isFalling = false;
	}
	if(isjumping)
	{
		isjumping = false;
	}
}

void PositionClass::SetFall()
{
	if(m_positionY > 1 && !isjumping)
	{
		isFalling = true;
		intPosY = 1;
	}
}
