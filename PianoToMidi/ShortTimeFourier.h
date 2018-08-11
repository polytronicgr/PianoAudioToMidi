#pragma once

class ShortTimeFourier
{
public:
	enum class STFT_WINDOW { RECT, HANN, HAMMING, BLACKMAN, BLACKMAN_HARRIS, FLAT_TOP, KAISER, TRIAG };

	explicit ShortTimeFourier(size_t frameLen = 2'048,
		STFT_WINDOW window = STFT_WINDOW::HANN, bool isPadReflected = true) noexcept;
	~ShortTimeFourier();

	void RealForward(const float* rawAudio, size_t nSamples, int hopLen = 0);
	const AlignedVector<std::complex<float>>& GetSTFT() const { return stft_; }
	size_t GetNumFrames() const { return nFrames_; }
private:
	void PadCentered(const float* source, size_t srcSize,
		AlignedVector<float>* dest, bool isModeReflect) const;
	void GetStftWindow(STFT_WINDOW window);

	const size_t frameLen_;
	const bool isPadReflect_;
	const byte pad_[sizeof(intptr_t) - sizeof(bool)]{ 0 };
	const std::unique_ptr<juce::dsp::FFT> fft_;
	std::unique_ptr<juce::dsp::WindowingFunction<float>> window_;

	AlignedVector<std::complex<float>> stft_;
	size_t nFrames_, nFreqs_;

	ShortTimeFourier(const ShortTimeFourier&) = delete;
	ShortTimeFourier operator=(const ShortTimeFourier&) = delete;
};