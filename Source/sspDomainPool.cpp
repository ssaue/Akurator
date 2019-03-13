/*
  ==============================================================================

    sspDomainPool.cpp
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainPool.h"
#include "sspDomainPrimitives.h"
#include "sspPlayer.h"
#include "sspPlayTask.h"
#include "sspTimeline.h"

#include "sspLogging.h"

#include <sstream>

template<typename T>
sspDomainPool<T>::sspDomainPool()
: sspDomainElement(), sspDomainVector<T>()
{
}

template <typename T>
bool sspDomainPool<T>::verify(int& nErrors, int& nWarnings) const
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

// Instantiate sspDomainPool templates
template class sspDomainPool<sspValue>;
template class sspDomainPool<sspConditional>;
template class sspDomainPool<sspString>;
template class sspDomainPool<sspPlayer>;
template class sspDomainPool<sspPlayTask>;
template class sspDomainPool<sspTimeline>;
