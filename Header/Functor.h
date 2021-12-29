#pragma once

template<typename T>
void Safe_Delete(T& Temp)
{
	if (Temp)
	{
		delete Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Delete_Array(T& Temp)
{
	if (Temp)
	{
		delete[] Temp;
		Temp = nullptr;
	}
}

template<typename T>
void Safe_Release(T& Temp)
{
	if (Temp)
	{
		Temp->Release();
		Temp = nullptr;
	}
}