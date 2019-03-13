/*
  ==============================================================================

    sspOSCPlayer.h
    Created: 17 Jan 2019 1:38:16pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspDomainVector.h"

#include <memory>
#include <boost/serialization/shared_ptr.hpp>

class sspOSCPlayer : public sspPlayer
{
	std::shared_ptr<sspString> address_;
	std::shared_ptr<sspString> path_;
	sspDomainVector<sspValue> arguments_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(address_);
		ar & BOOST_SERIALIZATION_NVP(path_);
		ar & BOOST_SERIALIZATION_NVP(arguments_);
	}

public:
	sspOSCPlayer();
	sspOSCPlayer(const sspOSCPlayer& obj) = delete;
	sspOSCPlayer& operator= (const sspOSCPlayer& obj) = delete;
	virtual ~sspOSCPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setArguments(const sspDomainVector<sspValue>& args) { arguments_ = args; }
	const sspDomainVector<sspValue>& getArguments() const { return arguments_; }

	void setAddress(std::shared_ptr<sspString> addr) { address_ = std::move(addr); }
	std::shared_ptr<sspString> getAddress() const { return address_; }

	void setPath(std::shared_ptr<sspString> path) { path_ = std::move(path); }
	std::shared_ptr<sspString> getPath() const { return path_; }

private:
	virtual bool update() override;
};
