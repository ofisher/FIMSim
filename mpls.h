/*
 * Public definitions pertaining to the Forwarding Plane Manager component.
 *
 * Permission is granted to use, copy, modify and/or distribute this
 * software under either one of the licenses below.
 *
 * Note that if you use other files from the Quagga tree directly or
 * indirectly, then the licenses in those files still apply.
 *
 * Please retain both licenses below when modifying this code in the
 * Quagga tree.
 *
 * Copyright (C) 2012 by Open Source Routing.
 * Copyright (C) 2012 by Internet Systems Consortium, Inc. ("ISC")
 */

/*
 * License Option 1: GPL
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

/*
 * License Option 2: ISC License
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice appear
 * in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef FPM_LSP_H_
#define FPM_LSP_H_

#include <netinet/in.h>//for ip address storage definitions

typedef enum nhlfe_operation_enum {
  PUSH = 0,
  POP = 1,
  SWAP = 2
} nhlfe_operation_enum_t;

typedef enum table_operation_enum {
  ADD_LSP = 0,
  REMOVE_LSP = 1,
} table_operation_enum_t;

typedef enum ip_version_enum {

  IPv4 = 4,


  IPv6 = 6,

} ip_version_enum_t;

typedef union ip4_or_6_address{
    in_addr_t ipv4;
    struct in6_addr ipv6;
  } ip4_or_6_address_t;

/*
 * Next Hop Label Forwarding Entry (NHLFE)
 * Used from FPM protocol version 1
 */
typedef struct nhlfe_msg_t_
{

  /*
   * The IP version (4 or 6) that the next hop field contains
   * values defined in ip_version_enum_t
   */

  uint8_t ip_version;

  /*
   * The next hop IP address. This
   * is used to look up the interface number the packet is
   * going out
   */

  ip4_or_6_address_t next_hop_ip;



  /*
   * What operation we are doing on the flow table (add, delete, in the future
   * perhaps modify), values defined in table_operation_enum_t
   */

  uint8_t table_operation;

  /*
   * Specifies if this is a push, pop or swap label operation.
   * Values defined in nhlfe_operation_enum_t
   */
  uint8_t nhlfe_operation;

  /*
   * In network byte order
   */

  uint32_t in_label;

  /*
   * In network byte order
   */

  uint32_t out_label;

} __attribute__((packed)) nhlfe_msg_t;


typedef struct ftn_msg_t_
{
  /*
   * The IP version (4 or 6) that we are matching on, and IP version of next hop
   * Values defined in ip_version_enum_t
   */

  uint8_t ip_version;

  uint8_t mask;

  /*
   * What operation we are doing on the flow table (add, delete, in the future
   * perhaps modify), values defined in table_operation_enum_t
   */

  uint8_t table_operation;

  ip4_or_6_address_t match_network_ip;

  /*
   * In network byte order
   */

  uint32_t out_label;

  /*
   * The next hop IP address. This
   * is used to look up the interface number the packet is
   * going out
   */

  ip4_or_6_address_t next_hop_ip;



} __attribute__((packed)) ftn_msg_t;
#endif  // FPM_LSP_H_
