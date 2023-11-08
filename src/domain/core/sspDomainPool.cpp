/*
  ==============================================================================

    sspDomainPool.cpp
    Created: 4 Jan 2019 11:08:42am
    Author:  sigurds

  ==============================================================================
*/

#include "sspDomainPool.h"
#include "domain/core/sspDomainPrimitives.h"
#include "domain/core/sspPlayer.h"
#include "sspPlayTask.h"
#include "sspTimeline.h"
#include "sspInput.h"

#include "access/sspLogging.h"

#include <sstream>
#include <typeinfo>

template<typename T>
sspDomainPool<T>::sspDomainPool() : sspSharedVector<T>()
{
}

template <typename T>
bool sspDomainPool<T>::verify(int& nErrors, int& nWarnings) const
{
	bool bReturn = true;
	if (this->empty()) {
		SSP_LOG_WRAPPER_WARNING(nWarnings, bReturn) << "Pool of " << typeid(T).name() << " is empty";
	}
	for (auto&& element : *this) {
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
template class sspDomainPool<sspInput>;
