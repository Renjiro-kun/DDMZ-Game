#pragma once
#include <dc/maple.h>
#include <cstdint>

typedef union rumble_fields {
  uint32_t raw;
  struct {
    /* Special Effects and motor select. The normal purupuru packs will
    only have one motor. Selecting MOTOR2 for these is probably not
    a good idea. The PULSE setting here supposably creates a sharp
    pulse effect, when ORed with the special field. */

    /** \brief  Yet another pulse effect.
        This supposedly creates a sharp pulse effect.
    */
    uint32_t special_pulse : 1;
    uint32_t : 3; // unused

    /** \brief  Select motor #1.

        Most jump packs only have one motor, but on things that do have more
       than one motor (like PS1->Dreamcast controller adapters that support
       rumble), this selects the first motor.
    */
    uint32_t special_motor1 : 1;
    uint32_t : 2; // unused

    /** \brief  Select motor #2.

        Most jump packs only have one motor, but on things that do have more
       than one motor (like PS1->Dreamcast controller adapters that support
       rumble), this selects the second motor.
    */
    uint32_t special_motor2 : 1;

    /** \brief  Ignore this command.

        Valid value 15 (0xF).

        Most jump packs will ignore commands with this set in effect1,
       apparently.
    */
    uint32_t fx1_powersave : 4;

    /** \brief  Upper nibble of effect1.

        This value works with the lower nibble of the effect2 field to
        increase the intensity of the rumble effect.
        Valid values are 0-7.

        \see    rumble_fields_t.fx2_lintensity
    */
    uint32_t fx1_intensity : 3;

    /** \brief  Give a pulse effect to the rumble.

        This probably should be used with rumble_fields_t.fx1_pulse as well.

        \see    rumble_fields_t.fx2_pulse
    */
    uint32_t fx1_pulse : 1;

    /** \brief  Lower-nibble of effect2.

        This value works with the upper nibble of the effect1
        field to increase the intensity of the rumble effect.
        Valid values are 0-7.

        \see    rumble_fields_t.fx1_intensity
    */
    uint32_t fx2_lintensity : 3;

    /** \brief  Give a pulse effect to the rumble.

        This probably should be used with rumble_fields_t.fx1_pulse as well.

        \see    rumble_fields_t.fx1_intensity
    */
    uint32_t fx2_pulse : 1;

    /** \brief  Upper-nibble of effect2.

        This apparently lowers the rumble's intensity somewhat.
        Valid values are 0-7.
    */
    uint32_t fx2_uintensity : 3;

    /* OR these in with your effect2 value if you feel so inclined.
       if you or the PULSE effect in here, you probably should also
       do so with the effect1 one below. */

    /** \brief  Give a decay effect to the rumble on some packs. */
    uint32_t fx2_decay : 1;

    /** \brief  The duration of the effect. No idea on units... */
    uint32_t duration : 8;
  };
} rumble_fields_t;


class PuruPuruManager
{
public:
    static PuruPuruManager& GetInstance()
    {
        static PuruPuruManager instance;
        return instance;
    }
public:
    void Init();
    void Shutdown();

    void Rumble(rumble_fields_t effect);
    void SetEnable(bool value);
    bool GetEnable() { return m_IsEnabled; }

private:
    PuruPuruManager() = default;
    ~PuruPuruManager() = default;
    PuruPuruManager(const PuruPuruManager&) = delete;
    PuruPuruManager& operator=(const PuruPuruManager&) = delete;
private:
    bool m_IsEnabled = false;
    static maple_device_t* m_PuruPuruDevice;
};