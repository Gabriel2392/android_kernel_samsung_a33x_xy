# SPDX-License-Identifier: GPL-2.0
dtb-y += exynos/s5e8825.dtb
dtbo-y += exynos/board/erd/s5e8825-erd8825_r11.dtbo
dtbo-y += exynos/board/erd/s5e8825-erd8825_r10.dtbo
dtbo-y += exynos/board/erd/s5e8825-erd8825.dtbo
dtbo-y += exynos/board/univ/s5e8825-universal8825_r00.dtbo
dtbo-y += samsung/a33x/a33x_eur_open_w00_r02.dtbo
dtbo-y += samsung/a33x/a33x_eur_open_w00_r03.dtbo
dtbo-y += samsung/a33x/a33x_eur_open_w00_r01.dtbo
dtbo-y += samsung/a33x/a33x_eur_open_w00_r00.dtbo
dtbo-y += samsung/a33x/a33x_eur_open_w00_r04.dtbo

targets += dtbs
DTB_LIST  := $(dtb-y) $(dtbo-y)
always-y  := $(DTB_LIST)

dtbs: $(addprefix $(obj)/, $(DTB_LIST))

clean-files := *.dtb*
