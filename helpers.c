/*
 * Copyright (c) 2014 Stoian Ivanov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

/**********************************************************************************
 * This code is part of HTTP-Live-Video-Stream-Segmenter-and-Distributor
 * look for newer versions at github.com
 **********************************************************************************/
#include "segmenter.h"

#include <stdio.h>
#include "libavformat/avformat.h"

void ffmpeg_version() {
	printBanner();
	// output build and version numbers
	fprintf(stderr, "libav versions:\n");
	fprintf(stderr, "  libavutil version:   %s\n", AV_STRINGIFY(LIBAVUTIL_VERSION));
	fprintf(stderr, "  libavutil build:     %d\n", LIBAVUTIL_BUILD);
	fprintf(stderr, "  libavcodec version:  %s\n", AV_STRINGIFY(LIBAVCODEC_VERSION));
	fprintf(stdout, "  libavcodec build:    %d\n", LIBAVCODEC_BUILD);
	fprintf(stderr, "  libavformat version: %s\n", AV_STRINGIFY(LIBAVFORMAT_VERSION));
	fprintf(stderr, "  libavformat build:   %d\n", LIBAVFORMAT_BUILD);
	
	fprintf(stderr, "This tool is version " PROGRAM_VERSION ",  built on " __DATE__ " " __TIME__);
	#ifdef __GNUC__
	fprintf(stderr, ", with gcc: " __VERSION__ "\n");
	#else
	fprintf(stderr, ", using a non-gcc compiler\n");
	#endif
}



void debugReturnCode(int r) {
	switch (r) {
		#if USE_OLD_FFMPEG
		case AVERROR_UNKNOWN:
			#else
		case AVERROR(EINVAL):
			#endif
			/**< unknown error */
			fprintf(stderr, "Unknown error.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_IO:
			#else
		case AVERROR(EIO):
			#endif             
			/**< I/O error */
			fprintf(stderr, "I/O error.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_NUMEXPECTED:
			#else
		case AVERROR(EDOM):
			#endif			    
			/**< Number syntax expected in filename. */
			fprintf(stderr, "Number syntax expected in filename.\n");
			break;
		case AVERROR_INVALIDDATA:
			/**< invalid data found */
			fprintf(stderr, "Invalid data found.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_NOMEM:
			#else
		case AVERROR(ENOMEM):
			#endif        
			/**< not enough memory */
			fprintf(stderr, "Not enough memory.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_NOFMT:
			#else
		case AVERROR(EILSEQ):
			#endif         
			/**< unknown format */
			fprintf(stderr, "Unknown format.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_NOTSUPP:
			#else
		case AVERROR(ENOSYS):
			#endif       
			/**< Operation not supported. */
			fprintf(stderr, "Operation not supported.\n");
			break;
			#if USE_OLD_FFMPEG
		case AVERROR_NOENT:
			#else
		case AVERROR(ENOENT):
			#endif        
			/**< No such file or directory. */
			fprintf(stderr, "No such file or directory.\n");
			break;
		case AVERROR_EOF:
			/**< End of file. */
			fprintf(stderr, "End of file.\n");
			break;
		case AVERROR_PATCHWELCOME:
			/**< Not yet implemented in FFmpeg. Patches welcome. */
			fprintf(stderr, "Not yet implemented in FFmpeg. Patches welcome.\n");
			break;
			#if USE_OLD_FFMPEG
			/**< Codes For Old FFMPEG Deprecated. */
			#else
			/**< New Error Codes For FFMPEG. */
			case AVERROR_BUG:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Internal bug. AVERROR_BUG\n");
				break;
#ifdef AVERROR_BUG2
			case AVERROR_BUG2:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Internal bug. AVERROR_BUG2.\n");
				break;
#endif
			case AVERROR_STREAM_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Stream not found.\n");
				break;
			case AVERROR_PROTOCOL_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Protocol not found.\n");
				break;
			case AVERROR_OPTION_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Option not found.\n");
				break;
			case AVERROR_MUXER_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Muxer not found. \n");
				break;
			case AVERROR_FILTER_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Filter not found.\n");
				break;
			case AVERROR_EXIT:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Immediate exit was requested; the called function should not be restarted.\n");
				break;
			case AVERROR_ENCODER_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Encoder not found.\n");
				break;
			case AVERROR_DEMUXER_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Demuxer not found.\n");
				break;
			case AVERROR_DECODER_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Decoder not found.\n");
				break;
			case AVERROR_BSF_NOT_FOUND:
				/**< Not yet implemented in FFmpeg. Patches welcome. */
				fprintf(stderr, "Bitstream filter not found.\n");
				break;
				#endif	
			default:
				fprintf(stderr, "Unknown return code: %d\n", r);
	}
}
