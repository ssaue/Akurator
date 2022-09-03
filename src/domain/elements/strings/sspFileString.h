/*
  ==============================================================================

    sspFileString.h
    Created: 14 Jan 2019 2:21:43pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspDomainPrimitives.h"
#include <boost/serialization/weak_ptr.hpp>

class sspFileString : public sspString
{
	std::weak_ptr<sspString> path_;
	bool recursive_;
	bool audio_only_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspString);
		ar & BOOST_SERIALIZATION_NVP(path_);
		ar & BOOST_SERIALIZATION_NVP(recursive_);
		ar & BOOST_SERIALIZATION_NVP(audio_only_);
	}

public:
	sspFileString();
	sspFileString(const sspFileString& cond) = delete;
	sspFileString& operator= (const sspFileString& cond) = delete;
	virtual ~sspFileString() {}

	// Virtual methods
	virtual std::string getString() const override;
	virtual bool verify(int& /*nErrors*/, int& /*nWarnings*/) const override;

	// Accessors
	void setPath(std::weak_ptr<sspString> str) { path_ = std::move(str); }
	void setRecursiveSearch(bool rec) { recursive_ = rec; }
	void setAudioOnly(bool audio) { audio_only_ = audio; }

	std::weak_ptr<sspString> getPath() const { return path_; }
	bool isRecursiveSearch() const { return recursive_; }
	bool isAudioOnly() const { return audio_only_; }

private:
	mutable std::string previous_path_ = { "" };
};

