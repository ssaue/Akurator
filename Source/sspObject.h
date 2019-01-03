/*
  ==============================================================================

    sspObject.h
    Created: 3 Jan 2019 12:28:24pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include <string>
#include <cereal\access.hpp>

class sspObject
{
protected:
	std::string name_ { "" };

public:
	sspObject() = default;
	sspObject(const sspObject& obj) = delete;
	sspObject& operator= (const sspObject& obj) = delete;
	virtual ~sspObject() {}

	const std::string& getName() const { return name_; }
	void setName(const std::string& name) { name_ = name; }

	// Verify correctness (returns false if there are errors or warnings)
	// Details on errors and warnings should be logged to file
	virtual bool verify(int& nErrors, int& nWarnings) = 0;

private:
	friend class cereal::access;
	template <class Archive>
	void save(Archive & ar) const {
		ar(CEREAL_NVP(name_));
	}

};
