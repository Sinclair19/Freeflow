/*
 * Copyright (c) 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006 Cisco Systems.  All rights reserved.
 * Copyright (c) 2005 PathScale, Inc.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef KERN_ABI_H
#define KERN_ABI_H

#include <linux/types.h>
#include <assert.h>
//#include <ccan/container_of.h>

#include <rdma/ib_user_verbs.h>

/*
 * The minimum and maximum kernel ABI that we can handle.
 */
#define IB_USER_VERBS_MIN_ABI_VERSION	3
#define IB_USER_VERBS_MAX_ABI_VERSION	6

struct ex_hdr {
	struct ib_uverbs_cmd_hdr hdr;
	struct ib_uverbs_ex_cmd_hdr ex_hdr;
};


/*
 * This file contains copied data from the kernel's include/uapi/rdma/ib_user_verbs.h,
 * now included above.
 *
 * Whenever possible use the definition from the kernel header and avoid
 * copying from that header into this file.
 */

struct ibv_kern_ipv4_filter {
	__u32 src_ip;
	__u32 dst_ip;
};

struct ibv_kern_spec_ipv4 {
	__u32  type;
	__u16  size;
	__u16 reserved;
	struct ibv_kern_ipv4_filter val;
	struct ibv_kern_ipv4_filter mask;
};

struct ibv_kern_spec {
	union {
		struct ib_uverbs_flow_spec_hdr hdr;
		struct ib_uverbs_flow_spec_eth eth;
		struct ibv_kern_spec_ipv4 ipv4;
		struct ib_uverbs_flow_spec_ipv4 ipv4_ext;
		struct ib_uverbs_flow_spec_esp esp;
		struct ib_uverbs_flow_spec_tcp_udp tcp_udp;
		struct ib_uverbs_flow_spec_ipv6 ipv6;
		struct ib_uverbs_flow_spec_gre gre;
		struct ib_uverbs_flow_spec_tunnel tunnel;
		struct ib_uverbs_flow_spec_mpls mpls;
		struct ib_uverbs_flow_spec_action_tag flow_tag;
		struct ib_uverbs_flow_spec_action_drop drop;
		struct ib_uverbs_flow_spec_action_handle handle;
		struct ib_uverbs_flow_spec_action_count flow_count;
	};
};

struct ib_uverbs_modify_srq_v3 {
	__u32 srq_handle;
	__u32 attr_mask;
	__u32 max_wr;
	__u32 max_sge;
	__u32 srq_limit;
	__u32 reserved;
};
#define _STRUCT_ib_uverbs_modify_srq_v3
enum { IB_USER_VERBS_CMD_MODIFY_SRQ_V3 = IB_USER_VERBS_CMD_MODIFY_SRQ };

struct ibv_create_qp_resp_v3 {
	__u32 qp_handle;
	__u32 qpn;
};

struct ibv_create_qp_resp_v4 {
	__u32 qp_handle;
	__u32 qpn;
	__u32 max_send_wr;
	__u32 max_recv_wr;
	__u32 max_send_sge;
	__u32 max_recv_sge;
	__u32 max_inline_data;
};

struct ibv_create_srq_resp_v5 {
	__u32 srq_handle;
};

#define _STRUCT_ib_uverbs_create_srq_v5
enum { IB_USER_VERBS_CMD_CREATE_SRQ_V5 = IB_USER_VERBS_CMD_CREATE_SRQ };

#define _STRUCT_ib_uverbs_create_qp_v4
enum { IB_USER_VERBS_CMD_CREATE_QP_V4 = IB_USER_VERBS_CMD_CREATE_QP };

#define _STRUCT_ib_uverbs_create_qp_v3
enum { IB_USER_VERBS_CMD_CREATE_QP_V3 = IB_USER_VERBS_CMD_CREATE_QP };
#endif /* KERN_ABI_H */