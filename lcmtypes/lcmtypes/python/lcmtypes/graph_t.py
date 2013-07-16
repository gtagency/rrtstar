"""LCM type definitions
This file automatically generated by lcm.
DO NOT MODIFY BY HAND!!!!
"""

import cStringIO as StringIO
import struct

import vertex_t

import edge_t

class graph_t(object):
    __slots__ = ["num_vertices", "vertices", "num_edges", "edges"]

    def __init__(self):
        self.num_vertices = 0
        self.vertices = []
        self.num_edges = 0
        self.edges = []

    def encode(self):
        buf = StringIO.StringIO()
        buf.write(graph_t._get_packed_fingerprint())
        self._encode_one(buf)
        return buf.getvalue()

    def _encode_one(self, buf):
        buf.write(struct.pack(">i", self.num_vertices))
        for i0 in range(self.num_vertices):
            assert self.vertices[i0]._get_packed_fingerprint() == vertex_t.vertex_t._get_packed_fingerprint()
            self.vertices[i0]._encode_one(buf)
        buf.write(struct.pack(">i", self.num_edges))
        for i0 in range(self.num_edges):
            assert self.edges[i0]._get_packed_fingerprint() == edge_t.edge_t._get_packed_fingerprint()
            self.edges[i0]._encode_one(buf)

    def decode(data):
        if hasattr(data, 'read'):
            buf = data
        else:
            buf = StringIO.StringIO(data)
        if buf.read(8) != graph_t._get_packed_fingerprint():
            raise ValueError("Decode error")
        return graph_t._decode_one(buf)
    decode = staticmethod(decode)

    def _decode_one(buf):
        self = graph_t()
        self.num_vertices = struct.unpack(">i", buf.read(4))[0]
        self.vertices = []
        for i0 in range(self.num_vertices):
            self.vertices.append(vertex_t.vertex_t._decode_one(buf))
        self.num_edges = struct.unpack(">i", buf.read(4))[0]
        self.edges = []
        for i0 in range(self.num_edges):
            self.edges.append(edge_t.edge_t._decode_one(buf))
        return self
    _decode_one = staticmethod(_decode_one)

    _hash = None
    def _get_hash_recursive(parents):
        if graph_t in parents: return 0
        newparents = parents + [graph_t]
        tmphash = (0x49189ad7b639b453+ vertex_t.vertex_t._get_hash_recursive(newparents)+ edge_t.edge_t._get_hash_recursive(newparents)) & 0xffffffffffffffff
        tmphash  = (((tmphash<<1)&0xffffffffffffffff)  + (tmphash>>63)) & 0xffffffffffffffff
        return tmphash
    _get_hash_recursive = staticmethod(_get_hash_recursive)
    _packed_fingerprint = None

    def _get_packed_fingerprint():
        if graph_t._packed_fingerprint is None:
            graph_t._packed_fingerprint = struct.pack(">Q", graph_t._get_hash_recursive([]))
        return graph_t._packed_fingerprint
    _get_packed_fingerprint = staticmethod(_get_packed_fingerprint)
