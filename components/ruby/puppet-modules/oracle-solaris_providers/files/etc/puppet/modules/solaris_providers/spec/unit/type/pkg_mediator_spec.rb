#!/usr/bin/env rspec
require 'spec_helper'

describe Puppet::Type.type(:pkg_mediator) do

  before do
    @class = described_class
    @profile_name = "pkgmediator"
  end

  it "should have :name as its keyattribute" do
    expect( @class.key_attributes).to be == [:name]
  end

  describe "when validating attributes" do
    [ :ensure, :version, :implementation ].each do |prop|
      it "should have a #{prop} property" do
        expect(@class.attrtype(prop)).to be == :property
      end
    end
  end

  describe "when validating values" do

    describe "for ensure" do
      error_pattern = /Invalid value/m
      def validate(ens)
         @class.new(:name => @profile_name, :ensure => ens)
      end

      [ "present", "absent" ].each do |newval|
        it "should accept a value of #{newval}" do
          expect { validate(newval) }.not_to raise_error
        end
      end
    end

    describe "for version" do
      def validate(ver)
         @class.new(:name => @profile_name, :version => ver)
      end

      [ "none", "None", "1", "1.2", "1.2.3" ].each do |v|
        it "should accept #{v}" do
          expect { validate v }.not_to raise_error
        end
      end

      [ "A", "1a", "1.2b" ].each do |v|
        it "should not accept #{v}" do
          expect { validate v }.to raise_error(Puppet::ResourceError)
        end
      end
    end  # version

    describe "for implementation" do
      def validate(imp)
         @class.new(:name => @profile_name, :implementation => imp)
      end

      [ "none", "None", "foo", "foo@1", "foo@1.2.3" ].each do |v|
        it "should accept #{v}" do
          expect { validate v }.not_to raise_error
        end
      end
        [ "foo bar", "foo 1", "foo@1.2b" ].each do |v|
      it "should not accept #{v}" do
          expect { validate v }.to raise_error(Puppet::ResourceError)
        end
      end
    end  # implementation
  end # validating values
  describe "when validating resource" do
    it "should not accept None for both implementation and version" do
         expect { @class.new(:name => @profile_name, :version => 'None', :implementation => "None") }.to raise_error(Puppet::ResourceError)
    end
  end
end
