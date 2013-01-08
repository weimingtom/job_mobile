#ifndef _ITIMER_H_
#define _ITIMER_H_

#include "header/TimeValue.h"				// CTimeValue


/*! Interface to the Timer System.
*/
namespace nMech
{
	namespace nTIME
	{
		////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////
		struct ITimer
		{
			virtual bool Init() = 0;
			//! reset the timer
			virtual void Reset() = 0;	

			//! update the timer every frame
			virtual void Update() = 0;

			//! return the current time as calculated by the last call to update
			virtual const float GetCurrTime() const = 0;

			//! return the current time as calculated by the last call to update
			//	virtual const CTimeValue GetFrameStart() const = 0;

			//! return the current time
			virtual const CTimeValue GetCurrTimePrecise() const = 0;

			//! return the current time at the moment of the call
			virtual const float GetAsyncCurTime()= 0;

			//! return the time passed from the last update
			virtual const float GetFrameTime() const = 0;

			//! enable/disable timer
			virtual void Enable(bool bEnable) = 0;

			//! return the current framerate
			virtual float	GetFrameRate() = 0;

			//! time profiling
			virtual float gfGetTime() = 0;

			//! time profiling
			virtual float MeasureTime(const char* comment) = 0;

			virtual TCHAR* GetCurrentTimeString(fname_t szCurrentTime)=0;
			virtual TCHAR* GetCurrentDateString(fname_t szCurrentFileName)=0;
		};


	}//namespace nTIME
	namespace nInterface
	{
		extern JBASE_API nTIME::ITimer* g_pITimer;
	}
	namespace nTIME
	{
		inline ITimer* Get_ITimer(){ return nInterface::g_pITimer;}

		// this class is used for automatic profiling of a section of the code.
		// create an instance of this class, and upon exiting from the code section
		template <typename time>
		class CITimerAutoProfiler
		{
		public:
			CITimerAutoProfiler (ITimer* pTimer, time& rTime):
			  m_rTime (rTime)
					{
						rTime -= pTimer->GetAsyncCurTime();
					}

			  ~CITimerAutoProfiler ()
					{
						m_rTime += nTIME::Get_ITimer()->GetAsyncCurTime();
					}

		protected:
			time& m_rTime;
		};

	}
}

// include this string AUTO_PROFILE_SECTION(pITimer, g_fTimer) for the section of code where the profiler timer must be turned on and off
// The profiler timer is just some global or static float or double value that accumulates the time (in seconds) spent in the given block of code
// pITimer is a pointer to the ITimer interface, g_fTimer is the global accumulator

#define AUTO_PROFILE_SECTION(pITimer, g_fTimer) nMech::nTIME::CITimerAutoProfiler<double> __section_auto_profiler(pITimer, g_fTimer)

#endif //_ITIMER_H_