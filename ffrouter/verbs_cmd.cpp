// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "verbs_cmd.h"
#include <stdio.h>

// int ibv_exp_cmd_query_device_resp(int cmd_fd, void* cmd_in, void* resp_out)
// {
// 	struct ib_uverbs_ex_query_device cmd;
// 	struct ib_uverbs_ex_query_device_resp resp;
// 	struct ib_uverbs_query_device_resp *r_resp;
// 	uint32_t comp_mask = 0;

// 	memset(&resp, 0, sizeof(resp));
// 	r_resp = IBV_RESP_TO_VERBS_RESP_EX(&resp,
// 					   struct ib_uverbs_ex_query_device_resp,
// 					   struct ib_uverbs_query_device_resp);

// 	memcpy(&cmd, cmd_in, sizeof(cmd));

// 	IBV_INIT_CMD_RESP_EXP(QUERY_DEVICE, &cmd, sizeof(cmd), 0,
// 			      &resp, sizeof(resp), 0);
// 	if (write(cmd_fd, &cmd, sizeof(cmd)) != sizeof(cmd))
// 		return errno;

// 	memcpy(resp_out, &resp, sizeof(resp));
// 	return 0;
// }


int ibv_cmd_query_qp_resp(struct ibv_context *ib_context, void* cmd_in, int cmd_size, void* resp_out)
{
	int cmd_fd = ib_context->cmd_fd;

	char cmd_inp[100];
	struct ib_uverbs_query_qp *cmd = (struct ib_uverbs_query_qp*)cmd_inp;
	struct ib_uverbs_query_qp_resp resp;

	int ret;
	//IBV_INIT_CMD_RESP(cmd, cmd_size, QUERY_QP, &resp, sizeof resp);
	cmd->qp_handle = ((struct ib_uverbs_query_qp *)cmd_in)->qp_handle;
	cmd->attr_mask = ((struct ib_uverbs_query_qp *)cmd_in)->attr_mask;

	//if (write(cmd_fd, cmd, cmd_size) != cmd_size)
	//	return errno;

	ret = execute_cmd_write(ib_context, IB_USER_VERBS_CMD_QUERY_QP, cmd,
				cmd_size, &resp, sizeof(resp));
	if (ret)
		return ret;

	memcpy(resp_out, &resp, sizeof(resp));
	return 0;
}

int ibv_cmd_create_flow_resp(int cmd_fd, void* cmd_in, int written_size, int exp_flow, void* resp_out)
{
	char cmd_inp[1024];
	struct ib_uverbs_create_flow *cmd = (struct ib_uverbs_create_flow*)cmd_inp;
	struct ib_uverbs_create_flow_resp resp;

	memcpy(cmd, cmd_in, written_size);

	int spec_size = sizeof(struct ibv_kern_spec);
	struct ibv_kern_spec *ib_spec = (struct ibv_kern_spec *)(cmd + 1);
	void *ib_spec_ptr = ib_spec;
	printf("exp_flow=%d, written_size=%d, num_of_specs: %d\n", exp_flow, written_size, cmd->flow_attr.num_of_specs);

	int i = 0;
	for (i = 0; i < cmd->flow_attr.num_of_specs; i++)
	{
		printf("spec.size=%d, spec.type=%x\n", ((struct ibv_kern_spec *)ib_spec_ptr)->hdr.size, ((struct ibv_kern_spec *)ib_spec_ptr)->hdr.type);
		ib_spec_ptr = ib_spec_ptr + ((struct ibv_kern_spec *)ib_spec_ptr)->hdr.size;
	}

	if (exp_flow)
		IBV_INIT_CMD_RESP_EXP(CREATE_FLOW, cmd, written_size, 0, &resp, sizeof(resp), 0);
	else
		IBV_INIT_CMD_RESP_EX_VCMD(cmd, written_size, written_size, CREATE_FLOW, &resp, sizeof(resp));

	if (write(cmd_fd, cmd, written_size) != written_size)
		return errno;

	memcpy(resp_out, &resp, sizeof(resp));
	return 0;
}

int ibv_cmd_destroy_flow_resp(int cmd_fd, void* cmd_in)
{
	struct ibv_destroy_flow cmd;

	memcpy(&cmd, cmd_in, sizeof cmd);
	IBV_INIT_CMD_EX(&cmd, sizeof(cmd), DESTROY_FLOW);

	if (write(cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;
	return 0;
}

