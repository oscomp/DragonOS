
/// impl
/// 
impl another_ext4::BlockDevice for super::GenDisk {
    fn read_block(&self, block_id: u64) -> another_ext4::Block {
        use another_ext4::BLOCK_SIZE;
        let mut buf = [0; BLOCK_SIZE];
        self.read_at(&mut buf, block_id as usize)
            .expect("read block error");
        another_ext4::Block::new(block_id, buf)
    }

    fn write_block(&self, block: &another_ext4::Block) {
        self.write_at(&block.data, block.id as usize)
            .expect("write block error");
    }
} 