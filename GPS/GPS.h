/*
* Copyright (c) 2012 Sebastien Jean.
* 
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the GNU Lesser Public License v3.0
* which accompanies this distribution, and is available at
* http://www.gnu.org/licenses/lgpl-3.0.html
* 
* Contributors:
*     Sebastien Jean - initial API and implementation
*/

#ifndef GPS_h
#define GPS_h

#include <inttypes.h>
#include <Stream.h>

/**
 * Maximum length of NMEA sentences (NMEA 0183 defines maximum as 82)
 */
#define MAX_NMEA_SENTENCE_LENGTH 85 // NMEA 0183 maximum is 82
/**
 * Status codes for GPS readings
 */
typedef enum {
	GPS_OK = 0,     //!< GPS_OK reading is successful
	GPS_TIMEOUT = 1,     //!< GPS_TIMEOUT timeout occured while reading
	GPS_NOT_NMEA = 2     //!< GPS_NOT_NMEA chars limit reached while reading
} GPS_status_enum;

/**
 * A NMEA GPS, taking its data from a serial port
 */
class GPS {
private:
	// per object data
	/**
	 * Serial input stream
	 */
	Stream *in;

	/**
	 * Reading timeout in milliseconds
	 */
	uint16_t millisecondsTimeout;

	/**
	 * Reading timeout in chars
	 */
	uint16_t charsTimeout;

	// private methods
	/**
	 * Reads an NMEA sentence
	 * @param nmeaString a string containing the beginning of the sentence to be read
	 * (e.g. "$GRMC"). Allocated buffer must be at least MAX_NMEA_SENTENCE_LENGTH long
	 *
	 * @return NMEA sentence reading status code
	 */
	GPS_status_enum readNMEA(char *nmeaString);

public:
	// public methods
	/**
	 * Creates a new GPS instance, reading data to <tt>in</tt> with timeouts set to
	 * <tt>millisecondsTimeout</tt> and <tt>charsTimeout</tt>
	 * @param in the input stream where to read data
	 * @param millisecondsTimeout reading timeout in milliseconds
	 * @param charsTimeout reading timeout in chars
	 */
	GPS(Stream *in, uint16_t millisecondsTimeout, uint16_t charsTimeout);

	/**
	 * Reads an RMC NMEA sentence
	 * @param nmeaString string where the RMC sentence will be stored.
	 * Allocated buffer must be at least MAX_NMEA_SENTENCE_LENGTH long
	 * @return NMEA sentence reading status code
	 */
	GPS_status_enum readRMC(char *nmeaString);

	/**
	 * Reads an GGA NMEA sentence
	 * @param nmeaString string where the RMC sentence will be stored.
	 * Allocated buffer must be at least MAX_NMEA_SENTENCE_LENGTH long
	 * @return NMEA sentence reading status code
	 */
	GPS_status_enum readGGA(char *nmeaString);

};
#endif
