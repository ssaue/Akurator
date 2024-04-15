/*
  ==============================================================================

    sspAudioStream.h
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspStream.h"
#include "engine/sspTimeUpdater.h"

#include <mutex>
#include <boost/serialization/weak_ptr.hpp>

class sspStreamBus;

class sspAudioStream : public sspStream
{
	std::weak_ptr<sspValue> volume_factor_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspStream);
		ar & BOOST_SERIALIZATION_NVP(volume_factor_);
	}

public:
	sspAudioStream();
	sspAudioStream(const sspAudioStream& obj) = delete;
	sspAudioStream& operator= (const sspAudioStream& obj) = delete;
	virtual ~sspAudioStream();

	virtual void start() override;
	virtual void update(double seconds) override;
	virtual void terminate() final;

	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage& msg) override;

	void setVolumeFactor(std::weak_ptr<sspValue> value) { volume_factor_ = std::move(value); }
	std::weak_ptr<sspValue> getVolumeFactor() const { return volume_factor_; }

	void setBus(std::unique_ptr<sspStreamBus> mixer);

private:
	bool replace(std::weak_ptr<sspPlayTask> task, std::weak_ptr<sspPlayTask> old_task) override;

	std::unique_ptr<sspStreamBus> bus_;
	double master_volume_ = 0.0;
	sspTimeUpdater updater_;
	bool is_solostream_ = false;
};

