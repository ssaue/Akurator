/*
  ==============================================================================

    sspOSCPlayer.h
    Created: 17 Jan 2019 1:38:16pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspPlayer.h"
#include "sspSharedVector.h"

#include <memory>
#include <boost/serialization/weak_ptr.hpp>

class sspOSCPlayer : public sspPlayer
{
	std::weak_ptr<sspString> address_;
	std::weak_ptr<sspString> path_;
	sspWeakVector<sspValue> arguments_;

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
	void setArguments(const sspWeakVector<sspValue>& args) { arguments_ = args; }
	const sspWeakVector<sspValue>& getArguments() const { return arguments_; }

	void setAddress(std::weak_ptr<sspString> addr) { address_ = std::move(addr); }
	std::weak_ptr<sspString> getAddress() const { return address_; }

	void setPath(std::weak_ptr<sspString> path) { path_ = std::move(path); }
	std::weak_ptr<sspString> getPath() const { return path_; }

private:
	virtual bool update() override;
};
