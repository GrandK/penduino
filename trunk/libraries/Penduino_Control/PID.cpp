/* 
 * File:   PID.cpp
 * Author: gavin
 * 
 * Created on 17 December 2010, 19:33
 */

#include "PID.h"
#include <avr/eeprom.h>

PID::PID(int pGainAddr, int iGainAddr, dGainAddr) {
  _pGainAddr = pGainAddr;
  _iGainAddr = iGainAddr;
  _dGainAddr = dGainAddr;
  
  _maxOut = 99999;
  _minOut = -99999;
  
  eeprom_read_block(&_pGainAddr, &_pGain, sizeof(double));
  eeprom_read_block(&_iGainAddr, &_iGain, sizeof(double));
  eeprom_read_block(&_dGainAddr, &_dGain, sizeof(double));
  
  _errorSum = 0;
  _lastError = 0;
}

double PID::getP(double error){
    return trim(pGain * error);
}

double PID::getPI(double error){
    double value = getP(error) + integral(error);
    return trim(value);
}

double PID::getPID(double error){
    double value = getP(error) + integral(error) + derivative(error);
	return trim(value);
}

double PID::integral(double error){
    //MUST ADD A BOUNDARY FOR ERRORSUMM

    errorSum+= error;
    return iGain * errorSum;
}

double PID::derivative(double error){
    double deriv = error - lastError;
    lastError = error;
    return deriv * dGain;
}

void PID::setPGain(double pGain){
  _pGain = pGain;
  eeprom_write_block(&_pGainAddr, &_pGain, sizeof(double));
}

void PID::setIGain(double iGain){
  _iGain = iGain;
  eeprom_write_block(&_iGainAddr, &_iGain, sizeof(double));
}

void PID::setDGain(double dGain){
  _dGain = dGain;
  prom_write_block(&_dGainAddr, &_dGain, sizeof(double));
}

void PID::setMaxOut(double maxOut){
  _maxOut = maxOut;
}

void PID::setMinOut(double minOut){
  _minOut = minOut;
}

double PID::trim(double value){
    if(value > _maxOut){
        value = _maxOut;
    } else if(value < _minOut){
        value = _minOut;
    }
    return value;
}



