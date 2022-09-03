/*
  ==============================================================================

    sspAudioStream.h
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspStream.h"
#include "engine/scheduling/sspTaskQueue.h"
#include "engine/sspTimeUpdater.h"

#include <mutex>
#include <boost/serialization/weak_ptr.hpp>

class sspStreamBus;

class sspAudioStream : public sspStream
{
	std::weak_ptr<sspValue> volume_factor_;
	unsigned int max_active_ = 0;
	unsigned int max_waiting_ = 0;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspStream);
		ar & BOOST_SERIALIZATION_NVP(volume_factor_);
		ar & BOOST_SERIALIZATION_NVP(max_active_);
		ar & BOOST_SERIALIZATION_NVP(max_waiting_);
	}

public:
	sspAudioStream();
	sspAudioStream(const sspAudioStream& obj) = delete;
	sspAudioStream& operator= (const sspAudioStream& obj) = delete;
	virtual ~sspAudioStream();

	virtual void start() override;
	virtual void update(double seconds) override;
	virtual void stop() final;
	virtual void terminate() final;
	virtual bool empty() const final;

	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage& msg) override;
	virtual void onFinished() override;

	void setVolumeFactor(std::weak_ptr<sspValue> value) { volume_factor_ = std::move(value); }
	std::weak_ptr<sspValue> getVolumeFactor() const { return volume_factor_; }

	// Set max number of tasks in each list (0 implies no limit)
	void   setMaxTasks(unsigned int active, unsigned int waiting);
	void   setBus(std::unique_ptr<sspStreamBus> mixer);

	unsigned int getMaxActive() const { return max_active_; }
	unsigned int getMaxWaiting() const { return max_waiting_; }

private:
	virtual void play(std::weak_ptr<sspPlayTask> task) final;

	sspTaskQueue task_queue_;
	std::unique_ptr<sspStreamBus> bus_;
	double master_volume_ = 0.0;
	sspTimeUpdater updater_;
	bool is_solostream_ = false;
};

