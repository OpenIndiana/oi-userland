#!/usr/bin/env ruby

require 'spec_helper'
provider_class = Puppet::Type.type(:pkg_mediator).provider(:pkg_mediator)

describe provider_class do

  before(:each) do
    # Create a mock resource
    @resource = Puppet::Type.type(:pkg_mediator).new(
      :name             => "foo",
      :ensure           => :present,
      :version          => "1.1.1",
      :implementation   => "a@1.2")
    @provider = provider_class.new(@resource)

    FileTest.stubs(:file?).with('/usr/bin/pkg').returns true
    FileTest.stubs(:executable?).with('/usr/bin/pkg').returns true
  end

  [ "version", "exists?", "implementation", "build_flags",
    "create", "destroy" ].each do |method|
    it "should have a #{method} method" do
      expect(@provider.class.method_defined?(method)).to be true
    end
  end

  describe ".instances" do
    it "should have an instances method" do
      expect(provider_class).to respond_to :instances
    end

    describe "should get a list of mediators" do
      provider_class.expects(:pkg).with(:mediator, "-H", "-F", "tsv").returns
      File.read(my_fixture('pkg_mediator.txt'))
      instances = provider_class.instances.map { |p| {
        :name             => p.get(:name),
        :ensure           => p.get(:ensure),
        :version          => p.get(:version),
        :implementation   => p.get(:implementation) } }

      it "with the expected number of instances" do
        expect(instances.size).to eq(5)
      end

      it "with version and implementation" do
        expect(instances[0]).to eq({
          :name             => 'foo',
          :ensure           => :present,
          :version          => '1.1.1',
          :implementation   => 'a@1.2'})
      end

      it "with version only" do
        expect(instances[1]).to eq({
          :name             => 'fooVer',
          :ensure           => :present,
          :version          => '1.1.1',
          :implementation   => :None})
      end

      it "with implementation only" do
        expect(instances[2]).to eq({
          :name             => 'fooImp',
          :ensure           => :present,
          :version          => :None,
          :implementation   => 'a@1.2'})
      end
    end
  end
end
