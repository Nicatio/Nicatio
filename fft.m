%imgTemp = imread('l9.bmp', 'bmp');

%imgTemp = imread('l5.bmp', 'bmp');
% G = fspecial('gaussian',[5 5],2);
% %# Filter it
% imgTemp = imfilter(imgTemp,G,'same');

%imgTemp = imread('11.bmp', 'bmp');
%imgTemp = imread('l9.bmp', 'bmp');
imgTemp = imread('yaleB01_P00A+000E+00.pgm', 'pgm');

% Normalize Image
imgLenna = double(imgTemp) ./ 255;

%-------------------------------------------------------------------------------
% Part 1 - 2D FFT
	mxLennaSize = size(imgLenna);
	intRows = mxLennaSize(1);
	intCols = mxLennaSize(2);
	
	imgLennaSpectrum = fftshift(fft2(imgLenna));
	
	% a)    log magnitude and phase
	imgLennaLogMag = log10(1+abs(imgLennaSpectrum));
	imgLennaPhase = angle(imgLennaSpectrum);
	
	% b)    Inverse FFT
	imgLennaInverseFFT = abs(ifft2(imgLennaSpectrum));
	
	% c)    Plots
	figure('Name', 'Part 1', 'NumberTitle', 'off', 'MenuBar', 'none');
	colormap('gray');
	subplot(2,2,1);
	imagesc(imgLenna);
	title('Original Image (lenna.gif)');
	
	subplot(2,2,2);
	imagesc(imgLennaLogMag);
	title('Log Maganitude of FFT of lenna.gif');
	
	subplot(2,2,3);
	imagesc(imgLennaPhase);
	title('Phase of FFT of lenna.gif');
	
	subplot(2,2,4);
	imagesc(imgLennaInverseFFT);
	title('Inverse FFT');