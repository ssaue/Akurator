/*
  ==============================================================================

    sspPool.cpp
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#include "sspPool.h"
#include "sspPrimitives.h"
#include "sspPlayer.h"
#include "sspPlayTask.h"
#include "sspTimeline.h"

#include "sspLogging.h"

#include <sstream>

template<typename T>
sspPool<T>::sspPool()
: sspObject(), sspObjectVector<T>()
{
}

template <typename T>
bool sspPool<T>::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;
	if (elements_.empty()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << getName() << " is empty";
	}
	for (auto&& element : elements_) {
		if (!element->verify(nErrors, nWarnings)) {
			bReturn = false;
		}
	}

	return bReturn;
}

// Instantiate sspPool templates
template class sspPool<sspValue>;
template class sspPool<sspConditional>;
template class sspPool<sspString>;
template class sspPool<sspPlayer>;
template class sspPool<sspPlayTask>;
template class sspPool<sspTimeline>;
