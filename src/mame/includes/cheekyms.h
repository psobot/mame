// license:BSD-3-Clause
// copyright-holders:Lee Taylor, Chris Moore
/*************************************************************************

    Cheeky Mouse

*************************************************************************/
#ifndef MAME_INCLUDES_CHEEKYMS_H
#define MAME_INCLUDES_CHEEKYMS_H

#pragma once

#include "audio/cheekyms.h"
#include "sound/dac.h"
#include "emupal.h"
#include "screen.h"
#include "tilemap.h"

class cheekyms_state : public driver_device
{
public:
	cheekyms_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_sound_board(*this, "soundboard")
		, m_gfxdecode(*this, "gfxdecode")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_videoram(*this, "videoram")
		, m_spriteram(*this, "spriteram")
		, m_port_80(*this, "port_80")
	{
	}

	DECLARE_INPUT_CHANGED_MEMBER(coin_inserted);

	void cheekyms(machine_config &config);

protected:
	virtual void machine_start() override;
	virtual void video_start() override;

private:
	void port_40_w(uint8_t data);
	void port_80_w(uint8_t data);

	INTERRUPT_GEN_MEMBER(vblank_irq);

	TILE_GET_INFO_MEMBER(get_tile_info);

	void cheekyms_palette(palette_device &palette) const;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);
	void draw_sprites(bitmap_ind16 &bitmap, const rectangle &cliprect, gfx_element *gfx, int flip);

	void io_map(address_map &map);
	void main_map(address_map &map);

	// devices
	required_device<cpu_device>             m_maincpu;
	required_device<cheekyms_audio_device>  m_sound_board;
	required_device<gfxdecode_device>       m_gfxdecode;
	required_device<screen_device>          m_screen;
	required_device<palette_device>         m_palette;

	// memory pointers
	required_shared_ptr<uint8_t>    m_videoram;
	required_shared_ptr<uint8_t>    m_spriteram;
	required_shared_ptr<uint8_t>    m_port_80;

	// video-related
	tilemap_t        *m_cm_tilemap = nullptr;
	std::unique_ptr<bitmap_ind16>       m_bitmap_buffer;

	uint8_t          m_irq_mask = 0U;
};

#endif // MAME_INCLUDES_CHEEKYMS_H
