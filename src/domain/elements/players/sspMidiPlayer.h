/*
  ==============================================================================

    sspMidiPlayer.h
	Created: 14 Nov 2023
	Author:  sigurds

  ==============================================================================
*/

#pragma once

#include "domain/core/sspPlayer.h"
#include "domain/core/sspSharedVector.h"

#include <memory>
#include <boost/serialization/weak_ptr.hpp>

class sspMidiPlayer : public sspPlayer
{
	std::weak_ptr<sspString> file_path_;
	std::weak_ptr<sspValue> tempo_factor_;

	friend class boost::serialization::access;
	template <typename Archive>
	void serialize(Archive & ar, const unsigned int /*version*/) {
		ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(sspPlayer);
		ar & BOOST_SERIALIZATION_NVP(file_path_);
		ar & BOOST_SERIALIZATION_NVP(tempo_factor_);
	}

public:
	sspMidiPlayer();
	sspMidiPlayer(const sspMidiPlayer& obj) = delete;
	sspMidiPlayer& operator= (const sspMidiPlayer& obj) = delete;
	virtual ~sspMidiPlayer() {}

	virtual bool start(std::weak_ptr<sspSendChannel> channel, std::weak_ptr<sspFinishedResponder> responder) override;
	virtual void stop() override;

	virtual bool isPlaying() const override;
	virtual bool verify(int& nErrors, int& nWarnings) const override;

	// Accessors
	void setFilepath(std::weak_ptr<sspString> file) { file_path_ = std::move(file); }
	std::weak_ptr<sspString> getFilepath() const { return file_path_; }

	void setTempoFactor(std::weak_ptr<sspValue> fact) { tempo_factor_ = std::move(fact); }
	std::weak_ptr<sspValue> getTempoFactor() const { return tempo_factor_; }

private:
	virtual bool update() override;
};
