/*
  ==============================================================================

    sspAudioStream.h
    Created: 1 Feb 2019 3:37:42pm
    Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "sspStream.h"
#include "sspTaskQueue.h"

#include <mutex>

class sspStreamMixer;

class sspAudioStream : public sspStream
{
	std::shared_ptr<sspValue> volume_factor_;
	size_t max_active_ = 0;
	size_t max_waiting_ = 0;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspStream);
		ar & BOOST_SERIALIZATION_NVP(volume_factor_);
		ar & BOOST_SERIALIZATION_NVP(max_active_);
		ar & BOOST_SERIALIZATION_NVP(max_waiting_);
	}

public:
	static double fadein_time_s, fadeout_time_s;

	sspAudioStream();
	sspAudioStream(const sspAudioStream& obj) = delete;
	sspAudioStream& operator= (const sspAudioStream& obj) = delete;
	virtual ~sspAudioStream();

	virtual void start() override;
	virtual void stop() final;
	virtual bool empty() const final;

	virtual bool verify(int& nErrors, int& nWarnings) const override;
	virtual void handleMessage(const sspMessage& msg) override;

	void setVolumeFactor(std::shared_ptr<sspValue> value) { volume_factor_ = std::move(value); }
	std::shared_ptr<sspValue> getVolumeFactor() const { return volume_factor_; }

	// Set max number of tasks in each list (0 implies no limit)
	void   setMaxTasks(size_t active, size_t waiting);
	void   setMixer(std::unique_ptr<sspStreamMixer> mixer);

	size_t getMaxActive() const { return max_active_; }
	size_t getMaxWaiting() const { return max_waiting_; }

private:
	virtual void play(std::weak_ptr<sspPlayTask> task) final;
	sspTaskQueue task_queue_;
	std::unique_ptr<sspStreamMixer> mixer_;
};

