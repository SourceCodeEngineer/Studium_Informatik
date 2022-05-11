"""
block format for a free block:
+----+---------------+--------------------------------+
|size|next_free_block|free space (size - 1 spaces)....|
+----+---------------+--------------------------------+

block format of a used block:
+----+--------------------------+
|size|user data (size spaces)...|
+----+--------------------------+

free blocks are identifies by being part of the chain started at the first free block that is pointed to be the first value in the pool

"""
BLOCK_OVERHEAD=1 # overhead of a full block
MIN_BLOCK_SIZE=1 # additional data required to manage a free block

class Pool:
	def __init__(self, N):
		self.pool = [0] * N
		self.pool[0] = 1 # pointer to first free block
		self.pool[1] = N - 2 # size of first block minus overhead
		self.pool[2] = None # next block; this is the only block

	def __getitem__(self, i):
		return self.pool[i]

	def malloc(self, size):
		block_size = 0
		prev_block = None
		cur_block = -1
		next_block = self.pool[0]
		while block_size < size:
			if next_block is None:
				return None
			block_size = self.pool[next_block]
			prev_block = cur_block
			cur_block = next_block
			next_block = self.pool[next_block + 1]
		if block_size - size < BLOCK_OVERHEAD + MIN_BLOCK_SIZE:
			# too little space for a new block
			# note that we do not restrict the block size even if it is possibly slightly too large in order to free the full amount afterwards
			self.pool[prev_block + 1] = next_block
		else:
			# create new block from remaining space
			self.pool[cur_block] = size
			self.pool[cur_block + BLOCK_OVERHEAD + size] = block_size - size - BLOCK_OVERHEAD
			self.pool[cur_block + BLOCK_OVERHEAD + size + 1] = next_block
			self.pool[prev_block + 1] = cur_block + BLOCK_OVERHEAD + size
		return cur_block + 1

	def free(self, index):
		freed_block = index - 1
		prev_free = -1
		next_free = self.pool[0]
		merged = False
		while True:
			if next_free is None or next_free > freed_block:
				if prev_free != -1 and prev_free + BLOCK_OVERHEAD + self.pool[prev_free] == freed_block:
					# merge the freed block with the free block before it
					self.pool[prev_free] += self.pool[freed_block] + 1 # combine size
					merged = True
					# allow for possible additional merge
					freed_block = prev_free

				if next_free is not None and freed_block + BLOCK_OVERHEAD + self.pool[freed_block] == next_free:
					# merge the freed block with the fee block following it
					self.pool[freed_block] += self.pool[next_free] + 1 # combine size
					self.pool[freed_block + 1] = self.pool[next_free + 1] # move next pointer
					if not merged:
						self.pool[prev_free + 1] = freed_block
					return

				# no merge possible
				self.pool[freed_block + 1] = self.pool[prev_free + 1]
				self.pool[prev_free + 1] = freed_block
				return

			prev_free = next_free
			next_free = self.pool[next_free + 1]

if __name__ == '__main__':
	print('test a:')
	p = Pool(200)
	a = p.malloc(50)
	print(a)
	p.free(a)
	print(p.malloc(190))

	print('test b:')
	p = Pool(200)
	a = p.malloc(50)
	b = p.malloc(50)
	print(a, b)
	p.free(a)
	p.free(b)
	print(p.malloc(190))

	print('test c:')
	p = Pool(200)
	a = p.malloc(50)
	b = p.malloc(50)
	c = p.malloc(50)
	print(a, b, c)
	p.free(b)
	p.free(a)
	p.free(c)
	print(p.malloc(190))

	print('test d:')
	p = Pool(200)
	a = p.malloc(50)
	b = p.malloc(50)
	c = p.malloc(50)
	print(a, b, c)
	p.free(a)
	print(p.malloc(50))
	p.free(b)
	print(p.malloc(50))
	p.free(c)
	print(p.malloc(50))

	print('test e:')
	p = Pool(200)
	a = p.malloc(50)
	b = p.malloc(50)
	c = p.malloc(50)
	print(a, b, c)
	p.free(c)
	p.free(b)
	print(p.malloc(50))
	print(p.malloc(50))
	p.free(a)
	print(p.malloc(50))
