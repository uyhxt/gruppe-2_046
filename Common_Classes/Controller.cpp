/*
 * Controller.cpp
 *
 *    Author: Henri Hornburg
 *     Email: henri.hornburg@student.kit.edu
 * Co-author: Max Zuidberg
 *     Email: m.zuidberg@icloud.com
 *
 * The controller class contains the algorithm which determines the motor
 * drive speeds based on an angle rate, an angle value and a steering position.
 */

#include "Controller.h"

Controller::Controller()
{
    /*
     * Default empty constructor
     */
}

Controller::~Controller()
{
    /*
     * Default empty destructor
     */
}

void Controller::init(System *sys, float maxSpeed)
{
    /*
     * Initialize the controller by configuring the working and behavior
     * variables.
     *
     * sys: Pointer to the current System instance.
     */

    // Create local reference to the given System object.
    ctlrSys = sys;

    // We use floats, therefore we want to profit from the FPU.
    // Check if it's already enabled and if not, enable it.
    ctlrSys->enableFPU();

    ctlrMaxSpeed = maxSpeed;

    // Initialize speed values
    resetSpeeds();
}

void Controller::resetSpeeds()
{
    /*
     * Reset all speed values to 0
     */

    ctlrDriveSpeed = 0.0f;
    ctlrLeftSpeed  = 0.0f;
    ctlrRightSpeed = 0.0f;
}

void Controller::updateValuesRad(float steeringValue, float angleRateRad,
                                 float accelHor, float accelVer)
{
    /*
     * Controller based on the P(I)D controller by http://www.tlb.org/#scooter
     * Careful! he uses radians, we too.
     */

    // Get angle from accelerometer and gyrometer. Factor by experiments.
    // Based on http://www.ups.bplaced.de/Dokumentation/Runner%207.38.pdf
    float angleAccelRad = atan2f(-accelHor, -accelVer);
    ctlrAngleRad = compFilter(integrate(ctlrAngleRad, angleRateRad),
                              angleAccelRad, CFG_CTLR_FILTER_FACT);

    // A low pass filter to prevent higher frequency oscillations (forward -
    // backward). Factor by experiments.
    ctlrAngleRate = compFilter(angleRateRad, ctlrAngleRate, CFG_CTLR_LOW_PASS_FACT);

    /*
     * Calculate torque needed for balance.
     * Note: the reduction of the factor 0.4 to 0.2 is needed to prevent
     * higher frequency oscillations (forward - backward). Factor by
     * experiments.
     */
    ctlrTorque = 5.0f * (ctlrAngleRad - ctlrAngleStableRad) + 0.2f * ctlrAngleRate;

    // Speed limiter
    float overspeed = ctlrDriveSpeed - ctlrMaxSpeed;
    if (overspeed > 0.0f)
    {
        // too fast
        overspeed = fminf(0.2f, overspeed + 0.05f);
        ctlrOverspeedInt = fminf(0.4f, integrate(ctlrOverspeedInt, overspeed));
    }
    else
    {
        overspeed = 0.0f;

        // stop speed limiter
        if (ctlrOverspeedInt > 0.0f)
        {
            ctlrOverspeedInt -= 0.04f / CFG_CTLR_UPDATE_FREQ;
        }
    }

    // New stable position
    ctlrAngleStableRad = 0.4f * overspeed + 0.7f * ctlrOverspeedInt;

    // Reduce steering when driving faster
    float steeringAdjusted = 0.07f / (0.3f + fabsf(ctlrDriveSpeed)) * steeringValue;

    // Update current drive speed
    ctlrDriveSpeed = integrate(ctlrDriveSpeed, 1.2f * ctlrTorque);

    // Apply steering
    ctlrLeftSpeed  = ctlrTorque + ctlrDriveSpeed + steeringAdjusted;
    ctlrRightSpeed = ctlrTorque + ctlrDriveSpeed - steeringAdjusted;

    ctlrSys->setDebugVal("Angle_[0.1deg]", ctlrAngleRad * 1800.0f / 3.14159f);
}

float Controller::getLeftSpeed()
{
    /*
     * Returns the duty cycle for the left motor as float. 
     * Note: Because the H-Bridges of the TivSeg can't be driven at a duty
     *       cycle of -1.0f or 1.0f the duty cycle is limited by the Config
     *       parameter CFG_CTLR_MAXDUTY. It is part of the Config.h and not of
     *       the controller class because this limit depends on the actual
     *       hardware (whose properties shall be defined in Config.h).
     */

    // The controller itself has no real limitation. Therefore it is done here.
    if (ctlrLeftSpeed > CFG_CTLR_MAXDUTY)
    {
        return CFG_CTLR_MAXDUTY;
    }
    else if (ctlrLeftSpeed < -CFG_CTLR_MAXDUTY)
    {
        return -CFG_CTLR_MAXDUTY;
    }

    return ctlrLeftSpeed;
}

float Controller::getRightSpeed()
{
    /*
     * Returns the duty cycle for the right motor as float. 
     * Note: Because the H-Bridges of the TivSeg can't be driven at a duty
     *       cycle of -1.0 or 1.0 the duty cycle is limited by the Config
     *       parameter CFG_CTLR_MAXDUTY. It is part of the Config.h and not of
     *       the controller class because this limit depends on the actual
     *       hardware (whose properties shall be defined in Config.h).
     */

    // The controller itself has no real limitation. Therefore it is done here.
    if (ctlrRightSpeed > CFG_CTLR_MAXDUTY)
    {
        return CFG_CTLR_MAXDUTY;
    }
    else if (ctlrRightSpeed < -CFG_CTLR_MAXDUTY)
    {
        return -CFG_CTLR_MAXDUTY;
    }

    return ctlrRightSpeed;
}

float Controller::getMaxSpeed()
{
    return ctlrMaxSpeed;
}

void Controller::setMaxSpeed(float speed)
{
    ctlrMaxSpeed = speed;
}

float Controller::integrate(float last, float current)
{
    /*
     * Integrates numerically.
     * Example: position = integrate(position, velocity)
     *
     * last:       Result of the last iteration
     * current:    value to integrate
     */

    return (last + current / CFG_CTLR_UPDATE_FREQ);
}

float Controller::arcTanDeg(float a, float b)
{
    /*
     * Returns arctan(a/b) in degree.
     */
    return (atan2f(a, b) * 180.0f / 3.14159265358979f);
}

float Controller::compFilter(float a, float b, float filterFactor)
{
    /*
     * Applies a complementary filter.
     */

    return (filterFactor * a + (1.0f - filterFactor) * b);
}
